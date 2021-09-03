#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator.hpp"
#include "reverse_iterator.hpp"

namespace	ft
{

template<typename T>
class	vector_iterator
	: public iterator<	random_access_iterator_tag,
						T >
{
public:
	vector_iterator() : _ptr(NULL) {}
	vector_iterator(const vector_iterator& ref) { *this = ref;}
	explicit vector_iterator(pointer ptr) : _ptr(ptr) {}
	~vector_iterator() {}

	vector_iterator&	operator=(const vector_iterator& ref)
	{
		if (this != &ref)
			_ptr = ref._ptr;
		return (*this);
	}

	vector_iterator&	operator+=(difference_type	n) { _ptr += n; return (*this); }
	vector_iterator		operator+(difference_type	n) { vector_iterator itr = (*this); return (itr += n); }
	vector_iterator&	operator-=(difference_type	n) { _ptr -= n; return (*this); }
	vector_iterator		operator-(difference_type	n) { vector_iterator itr = (*this); return (itr -= n); }
	reference			operator[](difference_type	n) { return (_ptr[n]); }
	// bool				operator<(vector_iterator	other) { return (_ptr < other._prt); }
	// bool				operator>(vector_iterator	other) { return (_ptr > other._prt); }
	// bool				operator<=(vector_iterator	other) { return !(_ptr > other._prt); }
	// bool				operator>=(vector_iterator	other) { return !(_ptr < other._prt); }

	template<typename U>
	vector_iterator&	operator=(vector_iterator<U>	other) { *this = other; return (*this); }

	vector_iterator		operator--()		{ return (--_ptr); }
	vector_iterator&	operator--(int)		{ vector_iterator	itr = (*this); --_ptr; return (itr); }
	vector_iterator		operator++()		{ return (++_ptr); }
	vector_iterator&	operator++(int)		{ vector_iterator	itr = (*this); ++_ptr; return (itr); }
	reference			operator*()			{ return (*_ptr); }
	pointer				operator->()		{ return (_ptr); }
	// bool				operator==(vector_iterator	other) { return (_ptr == other); }
	// bool				operator!=(vector_iterator	other) { return !(_ptr == other); }


template<typename iter>
friend	bool	operator==(
	const vector_iterator<iter>& lhs, const vector_iterator<iter>& rhs) { return (lhs._ptr == rhs._ptr); }
template<typename iter>
friend	bool	operator<(
	const vector_iterator<iter>& lhs, const vector_iterator<iter>& rhs) { return (lhs._ptr < rhs._prt); }
template<typename iter>
friend	difference_type		operator-(
	const vector_iterator<iter>& lhs, const vector_iterator<iter>& rhs) { return (lhs._ptr - rhs._prt); }

private:
	pointer	_ptr;

};

template<typename iter>
	bool				operator!=(
		const vector_iterator<iter>& lhs, const vector_iterator<iter>& rhs) { return !(lhs == rhs); }
template<typename iter>
	bool				operator>(
		const vector_iterator<iter>& lhs, const vector_iterator<iter>& rhs) { return (rhs < lhs); }
template<typename iter>
	bool				operator<=(
		const vector_iterator<iter>& lhs, const vector_iterator<iter>& rhs) { return !(rhs < lhs); }
template<typename iter>
	bool				operator>=(
		const vector_iterator<iter>& lhs, const vector_iterator<iter>& rhs) { return !(lhs < rhs); }

template<typename T>
vector_iterator<T> operator+(
	typename vector_iterator<T>::diffence_type n, const vector_iterator<T>& iterator) { vector_iterator itr = iterator; return (itr += n); }

}

#endif
