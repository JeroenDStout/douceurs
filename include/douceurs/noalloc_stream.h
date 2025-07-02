#pragma once

#include <string_view>
#include <iostream>
#include <sstream>

namespace douceurs::memory
{

    template <typename char_t>
    class nonallocating_stringbuf : public std::basic_streambuf<char_t> {
    public:
        nonallocating_stringbuf(std::basic_string_view<char_t> sv) {
            char_t* begin = const_cast<char_t*>(sv.data());
            this->setg(begin, begin, begin + sv.size());
        }
    };

    template <typename char_t>
    class nonallocating_istream : public std::basic_istream<char_t> {
    public:
        nonallocating_stringbuf<char_t> buffer;
        nonallocating_istream(std::basic_string_view<char_t> sv)
            : std::basic_istream<char_t>(&buffer), buffer(sv) {}
    };

}