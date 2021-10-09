#ifndef UTILS_HPP
#define UTILS_HPP

#include "iterator.hpp"

namespace ft
{

/* enable_if */
template <bool cond, typename T = void> struct enable_if {};
template <typename T> struct enable_if <true, T> { typedef T type; };


/* is_input_iter */
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
	struct	is_integral<unsigned char> : public is_integral_base<true, unsigned char> {};
template <>
	struct	is_integral<short> : public is_integral_base<true, short> {};
template <>
	struct	is_integral<unsigned short> : public is_integral_base<true, unsigned short> {};
template <>
	struct	is_integral<int> : public is_integral_base<true, int> {};
template <>
	struct	is_integral<unsigned int> : public is_integral_base<true, unsigned int> {};
template <>
	struct	is_integral<long> : public is_integral_base<true, long> {};
template <>
	struct	is_integral<unsigned long> : public is_integral_base<true, unsigned long> {};
template <>
	struct	is_integral<long long> : public is_integral_base<true, long long> {};
template <>
	struct	is_integral<unsigned long long> : public is_integral_base<true, unsigned long long> {};


/* distance */
template < typename InputIt >
	typename ft::iterator_traits<InputIt>::difference_type	distance(InputIt first, InputIt last)
	{
		typename ft::iterator_traits<InputIt>::difference_type	dist = 0;
		while (first != last){
			++first;
			++dist;
		}
		return dist;
	}


/* nullptr */
const class nullptr_t
{
public:
	template <typename T>
	operator T*() const { return 0; }

	template <typename T, typename U>
	operator T U::*() const { return 0; }

private:
	void operator&() const;

} my_nullptr = {};


/* lexicographical_compare */
template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}
template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1,*first2))
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}


/* equal */
template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1) {
			if (!pred(*first1,*first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}


template< class T1, class T2 >
struct pair
{
	typedef	T1	first_type;
	typedef	T2	second_type;

	first_type	first;
	second_type	second;

	pair()
	:
		first(),
		second()
	{}
template<class U, class V>
	pair (const pair<U,V>& pr)
	:
		first(pr.first),
		second(pr.second)
	{}
	pair (const first_type& a, const second_type& b)
	:
		first(a),
		second(b)
	{}
	pair& operator=( const pair& other )
	{
		if (this == &other)
			return (*this);
		this->first = other.first;
		this->second = other.second;
		return (*this);
	}

};

template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) { return (pair<T1,T2>(x,y)); }

template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs == rhs); }

template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs < lhs); }

template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs < lhs; }

template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs < rhs); }

template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef	Arg1	first_argument_type;
		typedef	Arg2	second_argument_type;
		typedef	Result	result_type;
	};

/* less */
template <class T>
	struct less : public binary_function <T, T, bool>
	{
		bool operator() (const T& x, const T& y) const { return (x < y);}
	};


/* red black tree node */
enum Color
{
	RED,
	BLACK,
	DBLACK
};

template<typename T>
struct tree_node
{
public:
	typedef T		value_type;
	typedef Color	color_type;

	value_type	value;
	tree_node*	parent;
	tree_node*	left;
	tree_node*	right;
	color_type	color;

	tree_node()
	:
		value(),
		parent(my_nullptr),
		left(my_nullptr),
		right(my_nullptr),
		color(RED)
	{}

	tree_node(const value_type& val, tree_node* parent = my_nullptr,
				tree_node* left = my_nullptr, tree_node* right = my_nullptr, color_type color = RED)
	:
		value(val),
		parent(parent),
		left(left),
		right(right),
		color(color)
	{}

	tree_node(const tree_node& other)
	:
		value(other.value),
		parent(other.parent),
		left(other.left),
		right(other.right),
		color(other.color)
	{}

	virtual ~tree_node() {}

	tree_node& operator= (const tree_node& other)
	{
		if (this == &other)
			return (*this);
		this->value = other.value;
		this->parent = other.parent;
		this->left = other.left;
		this->right = other.right;
		this->color = other.color;
		return (*this);
	}

	bool operator==(const tree_node& other)
	{
		if (this->value == other.value)
			return (true);
		return (false);
	}
	bool operator!=(const tree_node& other)
	{
		if (this->value != other.value)
			return (true);
		return (false);
	}

};

template <class T1, class T2>
	bool operator== (const tree_node<T1>& lhs, const tree_node<T2>& rhs)
	{ return lhs == rhs; }

template <class T1, class T2>
	bool operator!= (const tree_node<T1>& lhs, const tree_node<T2>& rhs)
	{ return (lhs != rhs); }

}

#endif
