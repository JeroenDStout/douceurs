#pragma once

#include <type_traits>

namespace douceurs::value {

    template<typename ret_t, typename variable_t, typename... arg_t>
    ret_t distill(variable_t const & var, [[maybe_unused]] arg_t const & ... arg) {
        if constexpr (std::is_same_v<variable_t, ret_t>)
          return var;
        else if constexpr (requires { var(); })
          return var();
        else if constexpr (requires { var(arg...); })
          return var(arg...);
        else
          static_assert(!std::is_same_v<ret_t, ret_t>, "No way to distill this value");
    }

    template<typename assign_t>
    auto con_invoke(bool condition, assign_t assign_lambda) -> std::invoke_result_t<assign_t> {
        if (condition)
          return assign_lambda();
        return {};
    }

}