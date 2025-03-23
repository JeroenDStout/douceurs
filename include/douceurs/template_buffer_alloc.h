#pragma once

#include "traits_container.h"

#include <string>
#include <span>

namespace douceurs::memory
{

    template<typename buffer_t_>
    struct buf_std
    {
        using buffer_t  = buffer_t_;
        using element_t = traits::array_element_t<buffer_t>;

        buffer_t &buffer;

        buf_std(buffer_t &ref)
        : buffer(ref) { ; }

        element_t *       data()                            { return buffer.data();  }
        element_t const * data() const                      { return buffer.data();  }
        element_t &       at(std::size_t idx)               { return buffer.at(idx); }
        element_t const & at(std::size_t idx) const         { return buffer.at(idx); }
        element_t &       operator[](std::size_t idx)       { return buffer[idx];    }
        element_t const & operator[](std::size_t idx) const { return buffer[idx];    }
        
        void resize(std::size_t size)
        {
            buffer.resize(size);
        }

        template<class iter_t>
        void assign(iter_t const begin, iter_t const end)
        {
            buffer.assign(begin, end);
        }
        
        buf_std<buffer_t>& operator=(buf_std<buffer_t>&&) = delete;
    };

}