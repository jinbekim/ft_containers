#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <memory>
#include "vector_iterator.hpp"

namespace ft
{

template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef	T								value_type;
	typedef	Alloc							allocator_type;
	typedef	allocator_type::reference		reference;
	typedef	allocator_type::const_reference	const_refrence;
	typedef	allocator_type::pointer			pointer;
	typedef	allocator_type::const_pointer	const_pointer;
	typedef	vector_iterator<T>				iterator;
	// typedef	const iterator					const_iterator;
	// typedef	const iterator					const_reverse_iterator;
	typedef	reverse_iterator<iterator>		reverse_iterator;
	typedef	ptrdiff_t						difference_type;
	typedef	size_t							size_type;

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
// begin
// Return iterator to beginning (public member function )
// end
// Return iterator to end (public member function )
// rbegin
// Return reverse iterator to reverse beginning (public member function )
// rend
// Return reverse iterator to reverse end (public member function )


// Capacity:
// size
// Return size (public member function )
// max_size
// Return maximum size (public member function )
// resize
// Change size (public member function )
// capacity
// Return size of allocated storage capacity (public member function )
// empty
// Test whether vector is empty (public member function )
// reserve
// Request a change in capacity (public member function )


// Element access:
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
		erase(pos, pos + 1);
	}
	iterator erase( iterator first, iterator last )
	{
		if (last - first <= 0) return last;
		for(iterator it = first; it != last; ++it)
			_alloc.destory(&*it);
		memmove(&*first, &*last, sizeof(value_type) * (last - first));

		return last;
	}

// swap
// Swap content (public member function )
	void clear()
	{
		erase(begin(), end());
		_size = 0;
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
	size_t				_capacity;
	size_t				_size;
	allocator_type		_alloc;
	pointer				_data;

	void	_move_datas(iterator pos, size_type size, difference_type length)
	{
		if (size == 0 || length == 0)
			return;



		for(iterator it = first; it != last; ++it)
			_alloc.construct(&*(it + (last - first)));

	}

};


}

#endif
