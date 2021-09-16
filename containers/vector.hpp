#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <memory>
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef	T													value_type;
	typedef	Alloc												allocator_type;
	typedef	typename allocator_type::reference					reference;
	typedef	typename allocator_type::const_reference			const_refrence;
	typedef	typename allocator_type::pointer					pointer;
	typedef	typename allocator_type::const_pointer				const_pointer;
	typedef	random_access_iterator<value_type>					iterator;
	typedef	reverse_iterator<iterator>							reverse_iterator;
	typedef	random_access_iterator<const value_type>			const_iterator;
	typedef	reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef	typename iterator_traits<iterator>::diffence_type	difference_type;
	typedef	typename allocator_type::size_type					size_type;
	/* constructor */
	vector(/* args */);
	vector(const vector& ref);
	~vector();
	vector& operator=(const vector& ref);





// default (1)
// explicit vector (const allocator_type& alloc = allocator_type());
// fill (2)
// explicit vector (size_type n, const value_type& val = value_type(),
//                  const allocator_type& alloc = allocator_type());
// range (3)
// template <class InputIterator>
//          vector (InputIterator first, InputIterator last,
//                  const allocator_type& alloc = allocator_type());
// copy (4)
// vector (const vector& x);



// Iterators:
	iterator			begin()		{ return _start; }
	iterator			end()		{ return _end; }
	reverse_iterator	rbegin()	{ return _end; }
	reverse_iterator	rend()		{ return _start; }


// Capacity:
	size_type	size()		const	{ return (_size); }
	size_type	max_size()	const	{ return _alloc.max_size(); }
	size_type	capacity()	const	{ return _capacity; }
	bool		empty()		const	{ return _size; }
	void		resize (size_type n, value_type val = value_type())
	{

	}
	void		reserse(size_type n)
	{

	}


// Element access:
reference	operator[] (size_type n);
// operator[]
// Access element (public member function )
// at
// Access element (public member function )
// front
// Access first element (public member function )
// back
// Access last element (public member function )

// Modifiers:
// assign
// Assign vector content (public member function )

// push_back
// Add element at the end (public member function )

// pop_back
// Delete last element (public member function )

// insert
// Insert elements (public member function )

// erase
// Erase elements (public member function )
	iterator erase( iterator pos )
	{
		return erase(pos, pos + 1);
	}
	iterator erase( iterator first, iterator last )
	{
		if (last - first <= 0) return last;
		for (iterator it = first; it != last; ++it)
			_alloc.destory(&*it);
		memmove(&*first, &*last, sizeof(value_type) * (last - first));
		return first;
	}

// swap
// Swap content (public member function )

	void clear()
	{
		while (_end != _start)
			_alloc.destroy(--_end);
	}

// Allocator:
// get_allocator
// Get allocator (public member function )

// Non-member function overloads
// relational operators
// Relational operators for vector (function template )
// swap
// Exchange contents of vectors (function template )

// Template specializations
// vector<bool>
// Vector of bool (class template specialization )


private:
	allocator_type		_alloc;
	pointer				_start;
	pointer				_end;
	pointer				_end_capa;

};


}

#endif
