#ifndef IS_INPUT_ITER_HPP
#define IS_INPUT_ITER_HPP

#include "iterator.hpp"

namespace ft
{
template <bool is_valid, typename T>
	struct is_input_iter_base { typedef T type; const static bool value = is_valid; };

template <typename iter>
	struct is_input_iter : public is_input_iter_base<false, iter> {};

template<>
	struct is_input_iter<ft::random_access_iterator_tag>
		: public is_input_iter_base<true, ft::random_access_iterator_tag> {};
template<>
	struct is_input_iter<ft::bidirectional_iterator_tag>
		: public is_input_iter_base<true, ft::bidirectional_iterator_tag> {};
template<>
	struct is_input_iter<ft::forward_iterator_tag>
		: public is_input_iter_base<true, ft::forward_iterator_tag> {};
template<>
	struct is_input_iter<ft::input_iterator_tag>
		: public is_input_iter_base<true, ft::input_iterator_tag> {};
}

#endif
