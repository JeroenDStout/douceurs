#pragma once

#include <fstream>
#include <string>

namespace douceurs::io
{

    enum class slurp_ret { success, failure };

    // Note we intentionally use std string, as ifstream requires a guaranteed 0-terminated string
    template<typename buffer_t>
    auto slurp(buffer_t &out_buffer, std::string path) -> slurp_ret
    {
        try {
            std::ifstream file(path, std::ios_base::binary);
            out_buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
            return slurp_ret::success;
        }
        catch (...) {
        }

        return slurp_ret::failure;
    }

    auto is_success(slurp_ret val)
    {
        return val == slurp_ret::success;
    }

    auto is_failure(slurp_ret val)
    {
        return !is_success(val);
    }

}