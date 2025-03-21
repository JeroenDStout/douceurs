#pragma once

#include <string>
#include <span>

namespace douceurs::memory
{

    template<typename buffer_t_>
    struct buf_std
    {
        using buffer_t = buffer_t_;

        buffer_t &buffer;

        buf_std(buffer_t &ref)
        : buffer(ref) { ; }
        
        template<class iter_t>
        void assign(iter_t const begin, iter_t const end)
        {
            buffer.assign(begin, end);
        }
        
        buf_std<buffer_t>& operator=(buf_std<buffer_t>&&) = delete;
    };

}