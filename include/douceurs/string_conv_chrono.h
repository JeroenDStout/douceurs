#pragma once

/*
 *  ...
 */

 #include "noalloc_stream.h"
 
 #include <chrono>
 #include <string_view>

namespace douceurs::strings {

    // ...
    template <typename duration_t, typename fallback_t = std::chrono::sys_time<duration_t>>
    std::chrono::sys_time<duration_t> to_chrono(std::string_view const& view,
                                                std::string_view const& format,
                                                fallback_t fallback)
    {
        using timepoint_t = std::chrono::sys_time<duration_t>;
        memory::nonallocating_istream<char> in(view);

        timepoint_t result;

        if (std::chrono::from_stream(in, format.data(), result))
          return result;

        return value::distill<timepoint_t>(fallback, view);
    }

} 