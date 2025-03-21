#pragma once

#include <type_traits>

namespace douceurs::value {

    template<typename assign_t>
    auto con_invoke(bool condition, assign_t assign_lambda) -> std::invoke_result_t<assign_t> {
        if (condition)
          return assign_lambda();
        return {};
    }

}