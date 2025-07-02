#pragma once

/*
 *  ...
 */
 
 #include "def_value.h"

 #include <charconv>
 #include <string_view>

namespace douceurs::strings {

    // ...
    template <typename return_t, typename fallback_t>
    return_t convert_to(const std::string_view& view, fallback_t fallback)
    {
        return_t result;

        auto [ptr, ec] = std::from_chars(view.data(), view.data() + view.size(), result);
        if (ec == std::errc())
          return result;

        return value::distill<return_t>(fallback, view);
    }

}