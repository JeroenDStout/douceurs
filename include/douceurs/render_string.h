#pragma once

/*
 *  ...
 */
 
 #include "once.h"

 #include <string_view>
 #include <span>

namespace douceurs::strings {
    
    struct render_dbg_vars_style_brief
    { static constexpr bool quote_key() { return false; }};
    struct render_dbg_vars_style_json
    { static constexpr bool quote_key() { return true;  }};

    // Add an array-like of values to a stream
    template <typename style_t, typename stream_t, typename callback_t>
    inline void render_dbg_vars_array(stream_t &stream, callback_t callback);

    namespace detail {
        template <typename style_t, typename stream_t, typename val_t>
        inline void render_dbg_vars_value(stream_t &stream, val_t &val);

        // Add a span of values to a stream, see below
        template <typename style_t, typename stream_t, typename val_t>
        inline void render_dbg_vars_span(stream_t &stream, std::span<val_t> span)
        {
            render_dbg_vars_array<style_t>(stream,
              [span](auto callback) {
                 for (auto const &elem : span)
                   callback(elem);
              }
            );
        }

        // Add a variety of value types to a stream, see below
        template <typename style_t, typename stream_t, typename val_t>
        inline void render_dbg_vars_value(stream_t &stream, val_t &val)
        {
            // Check if we can invoke the value with our stream...
            if constexpr (requires { val(stream); })
              val(stream);
            // ...or whether we can invoke it without argument...
            else if constexpr (requires { val(); })
              stream << val();
            // ...or whether we should render it as a span...
            else if constexpr (requires { render_dbg_vars_span<style_t>(stream, val); })
              render_dbg_vars_span<style_t>(stream, val);
            // ...or an arithmetic type (which does not need quotation marks)...
            else if constexpr (std::is_arithmetic_v<val_t>)
              stream << val;
            // ...or whether we should render it as a string...
            else if constexpr (std::is_convertible_v<val_t, std::string_view>)
              stream << "\"" << val << "\"";
            else
            // ...or just add it to the stream
              stream << "\"" << val << "\"";
        }

        // Implementation detail for render_dbg_vars, see below 
        template <bool first, typename style_t, typename stream_t, typename key_t, typename val_t, typename... runon_t>
        inline void render_dbg_vars_recursive(stream_t &stream, key_t &key, val_t &val, runon_t const & ... runon)
        {
            // Open or continue
            stream << (first ? "{ " : ", ");

            // Render the key with or without quotation marks
            if constexpr (style_t::quote_key())
              stream << "\"" << key << "\" : ";
            else
              stream << key << " : ";

            render_dbg_vars_value<style_t>(stream, val);

            // If we have more arguments, continue recursively
            if constexpr (sizeof...(runon) > 0)
              render_dbg_vars_recursive<false, style_t>(stream, runon...);
            else
              stream << " }";
        }
    }
    
    // Recursively go through arguments, each time taking a key-value pair
    // Takes a style_t typename, which determines specifics of the text rendering
    // If the value is invocable with the stream, it is invoked with the stream argument
    // If the value is invocable without arguments, its return value is added to the stream
    // If the value is convertible to a string_view, it is rendered with quotation marks
    template <typename style_t, typename stream_t, typename... runon_t>
    inline void render_dbg_vars(stream_t &stream, runon_t const & ... runon)
    {
        static_assert(sizeof...(runon) % 2 == 0, "dbg_vars arguments are required to be pairs");

        if constexpr (sizeof...(runon) > 0)
          detail::render_dbg_vars_recursive<true, style_t>(stream, runon...);
        else
          stream << "{}";
    }

    // Add an array-like of values to a stream
    template <typename style_t, typename stream_t, typename callback_t>
    inline void render_dbg_vars_array(stream_t &stream, callback_t callback)
    {
        stream << "[";

        sugar::once once;
        callback([&once, &stream](auto &val) {
          if (!once())
            stream << ", ";
          detail::render_dbg_vars_value<style_t>(stream, val);
        });

        stream << "]";
    }

}
