#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include "enable_if.hpp"

namespace ft
{

/* is_integral */
template <bool is_itegral, typename T>
	struct is_integral_base {
		typedef T type;
		const static bool value = is_itegral;
	};


template <typename>
	struct	is_integral : public is_integral_base<false, void> {};

template <>
	struct	is_integral<bool> : public is_integral_base<true, bool> {};
template <>
	struct	is_integral<char> : public is_integral_base<true, char> {};
template <>
	struct	is_integral<signed char> : public is_integral_base<true, signed char> {};
template <>
	struct	is_integral<unsigned char> : public is_integral_base<true, unsigned char> {};
template <>
	struct	is_integral<short> : public is_integral_base<true, short> {};
template <>
	struct	is_integral<signed short> : public is_integral_base<true, signed short> {};
template <>
	struct	is_integral<unsigned short> : public is_integral_base<true, unsigned short> {};
template <>
	struct	is_integral<int> : public is_integral_base<true, int> {};
template <>
	struct	is_integral<signed int> : public is_integral_base<true, signed int> {};
template <>
	struct	is_integral<unsigned int> : public is_integral_base<true, unsigned int> {};
template <>
	struct	is_integral<long> : public is_integral_base<true, long> {};
template <>
	struct	is_integral<signed long> : public is_integral_base<true, signed long> {};
template <>
	struct	is_integral<unsigned long> : public is_integral_base<true, unsigned long> {};
template <>
	struct	is_integral<long long> : public is_integral_base<true, long long> {};
template <>
	struct	is_integral<signed long long> : public is_integral_base<true, signed long long> {};
template <>
	struct	is_integral<unsigned long long> : public is_integral_base<true, unsigned long long> {};

}
#endif
