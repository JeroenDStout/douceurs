#pragma once

#include <type_traits>

namespace douceurs::traits {

    // Gets the element type of an array-like, the return type of array[int]
    template<class array_t>
    using array_element_t = std::remove_reference_t<decltype(std::declval<array_t&>()[std::size_t{}])>;

}
