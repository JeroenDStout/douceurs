#pragma once

#include <type_traits>

namespace douceurs::traits
{
	namespace detail
	{
		template <typename ret_t, typename ... runon>
		std::tuple<runon...> get_argument(ret_t (*)(runon...));

		template <typename func_t, typename ret_t, typename... runon>
		std::tuple<runon...> get_arguments(ret_t (func_t::*)(runon...));

		template <typename func_t, typename ret_t, typename... runon>
		std::tuple<runon...> get_arguments(ret_t (func_t::*)(runon...) const);

		template <typename func_t>
		decltype(get_arguments(&func_t::operator())) get_arguments(func_t);

	}; 

	// Get a tuple with identical types of a function
	template <typename func_t>
	using arg_tuple = decltype(detail::get_arguments(std::declval<func_t>()));

	// Get the number of arguments of a function
	template <typename func_t>
	using arg_count = std::tuple_size<arg_tuple<func_t>>;

	// Get the type of nth argument (0-indexed)
	template <typename func_t, std::size_t idx>
	using arg_type = std::tuple_element_t<idx, arg_tuple<func_t>>;

	// Get whether the arguments of a function equal the types of a tuple
	template <typename func_t, typename ... runon>
	constexpr bool arg_equal = std::is_same_v<arg_tuple<func_t>, std::tuple<runon...>>;

}
