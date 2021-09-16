#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace	ft
{

template<typename Iterator>
class reverse_iterator
	: public iterator<	iterator_traits<Iterator>::iterator_category,
						iterator_traits<Iterator>::iterator_value_type,
						iterator_traits<Iterator>::iterator_difference_type,
						iterator_traits<Iterator>::iterator_pointer,
						iterator_traits<Iterator>::iterator_reference>
{
public:
	typedef	Iterator	iterator_type;

	reverse_iterator() : _iter() {};
	template <typename U>
	reverse_iterator(const reverse_iterator<U>& ref) { *this = ref; }
	explicit reverse_iterator(iterator_type iter) : _iter(iter) {} /* to prevent  -> reverse_iterator rit `=` it */
	~reverse_iterator() {}

	template <typename U>
	reverse_iterator& operator=(const reverse_iterator<U>& ref)
	{
		if (this != &ref)
			_iter = ref._iter;
		return (*this);
	}

	iterator_type		base() const { return (_iter); }

	/* random_access_iterator */
	reverse_iterator&	operator+=(difference_type	n) { _iter -= n; return (*this); }
	reverse_iterator	operator+(difference_type	n) { reverse_iterator itr = (*this); return (itr -= n); }
	reverse_iterator&	operator-=(difference_type	n) { _iter += n; return (*this); }
	reverse_iterator	operator-(difference_type	n) { reverse_iterator itr = (*this); return (itr += n); }
	reference			operator[](difference_type	n) const { return *(_iter - n - 1); }
	difference_type		operator-(reverse_iterator	other) { return (other._iter - _iter); }

	reverse_iterator	operator--()		{ return (++iter); }
	reverse_iterator&	operator--(int)		{ reverse_iterator	itr = (*this); ++iter; return (itr); }

	reverse_iterator	operator++()		{ return (--iter); }
	reverse_iterator&	operator++(int)		{ reverse_iterator	itr = (*this); --iter; return (itr); }
	reference			operator*()	const	{ return *(iter - 1); }
	pointer				operator->()		{ return (iter - 1); }

	template <typename iter>
		friend bool operator== (const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return (lsh._iter == rhs._iter); }

	template <typename iter>
		friend	bool operator< (const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return (lhs._iter > rhs._iter); }


private:
	iterator_type	_iter;

};

	template <typename iter>
		bool operator !=	(const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return !(lsh == rsh); }
	template <typename iter>
		bool operator <=	(const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return !(lhs < rhs); }
	template <typename iter>
		bool operator >		(const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return (lhs < rhs); }
	template <typename iter>
		bool operator >=	(const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return !(rhs < lhs); }

	template <typename iter>
		reverse_iterator<iter> operator +	(typename reverse_iterator<iter>::difference_type n, const reverse_iterator<iter>& rev_it) { return (rev_it - n); }
	template <typename iter>
		typename reverse_iterator<iter>::difference_type operator -	(const reverse_iterator<iter>& lhs, const reverse_iterator<iter>& rhs) { return (rhs - lhs); }

}

#endif
