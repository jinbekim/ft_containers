#ifndef IS_INTEGRAL
#define IS_INTEGRAL
#include "enable_if.hpp"

namespace ft
{
/* Integral types
** Signed integer types:	signed char, short int, int, long int, long long int
** Unsigned integer types:	unsigned char, unsigned short int, unsigned int, unsigned long int, unsigned long long int
*/
template < typename T>
	struct	is_integral { bool value = false; };

template <>
	struct	is_integral <bool> { bool value = true; };
template <>
	struct	is_integral <char> { bool value = true; };
template <>
	struct	is_integral <signed char> { bool value = true; };
template <>
	struct	is_integral <unsigned char> { bool value = true; };
template <>
	struct	is_integral <short> { bool value = true; };
template <>
	struct	is_integral <signed short> { bool value = true; };
template <>
	struct	is_integral <unsigned short> { bool value = true; };
template <>
	struct	is_integral <int> { bool value = true; };
template <>
	struct	is_integral <signed int> { bool value = true; };
template <>
	struct	is_integral <unsigned int> { bool value = true; };
template <>
	struct	is_integral <long> { bool value = true; };
template <>
	struct	is_integral <signed long> { bool value = true; };
template <>
	struct	is_integral <unsigned long> { bool value = true; };
template <>
	struct	is_integral <long long> { bool value = true; };
template <>
	struct	is_integral <signed long long> { bool value = true; };
template <>
	struct	is_integral <unsigned long long> { bool value = true; };

}
#endif
