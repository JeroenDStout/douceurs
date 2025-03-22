#pragma once

/*
 *  ...
 */

 #include <string_view>
 #include <type_traits>

namespace douceurs::strings {

    // Get a string_view with a sanity check for nullptr
    template <typename val_t>
    inline auto safe_view(val_t const &string) -> std::string_view
      requires std::is_convertible_v<val_t, std::string_view>
    {
        // For a ptr, check nullptr and return a view
        if constexpr (std::is_pointer_v<val_t>)
        {
            if (string == nullptr)
              return {};
            return string;
        }
        // ...otherwise, just use the default return or conversion
        else {
            return string;
        }
    }

    // For a list of string_view-likes return the first non-empty candidate, or empty
    template <typename candidate_t, typename... runon_t>
    inline auto fallback(candidate_t const &candidate, runon_t const & ... runon) -> std::string_view
    {
        std::string_view candidate_view = safe_view(candidate);
        if (candidate_view.size() > 0)
          return candidate_view;

        if constexpr (sizeof...(runon) > 0)
          return fallback(runon...);
        else
          return {};
    }

}
