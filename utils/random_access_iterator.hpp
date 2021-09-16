#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"
// #include "reverse_iterator.hpp"

namespace	ft
{

template<typename T>
class	random_access_iterator
	: public iterator<	random_access_iterator_tag, T >
{
public:
	random_access_iterator() : _ptr(NULL) {}
	random_access_iterator(const random_access_iterator& ref) { *this = ref;}
	explicit random_access_iterator(pointer ptr) : _ptr(ptr) {}
	~random_access_iterator() {}

	random_access_iterator&	operator=(const random_access_iterator& ref)
	{
		if (this != &ref)
			_ptr = ref._ptr;
		return (*this);
	}

	random_access_iterator&		operator+=(difference_type	n) { _ptr += n; return (*this); }
	random_access_iterator		operator+(difference_type	n) { random_access_iterator itr = (*this); return (itr += n); }
	random_access_iterator&		operator-=(difference_type	n) { _ptr -= n; return (*this); }
	random_access_iterator		operator-(difference_type	n) { random_access_iterator itr = (*this); return (itr -= n); }
	reference					operator[](difference_type	n) { return (_ptr[n]); }

	template<typename U>
	random_access_iterator&		operator=(random_access_iterator<U>	other) { *this = other; return (*this); }
	random_access_iterator		operator--()		{ return (--_ptr); }
	random_access_iterator&		operator--(int)		{ random_access_iterator	itr = (*this); --_ptr; return (itr); }
	random_access_iterator		operator++()		{ return (++_ptr); }
	random_access_iterator&		operator++(int)		{ random_access_iterator	itr = (*this); ++_ptr; return (itr); }
	reference					operator*()			{ return (*_ptr); }
	pointer						operator->()		{ return (_ptr); }

	template<typename iter>
	friend	bool				operator==(
		const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return (lhs._ptr == rhs._ptr); }
	template<typename iter>
	friend	bool				operator<(
		const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return (lhs._ptr < rhs._prt); }
	template<typename iter>
	friend	difference_type		operator-(
		const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return (lhs._ptr - rhs._prt); }

private:
	pointer	_ptr;

};

	template<typename iter>
		bool	operator !=	(const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return !(lhs == rhs); }
	template<typename iter>
		bool	operator >	(const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return (rhs < lhs); }
	template<typename iter>
		bool	operator <=	(const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return !(rhs < lhs); }
	template<typename iter>
		bool	operator >=	(const random_access_iterator<iter>& lhs, const random_access_iterator<iter>& rhs) { return !(lhs < rhs); }
	template<typename T>
		random_access_iterator<T>
			operator +	(typename random_access_iterator<T>::diffence_type n, const random_access_iterator<T>& iterator)
			{ random_access_iterator itr = iterator; return (itr += n); }

}

#endif
