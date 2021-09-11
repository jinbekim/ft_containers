#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <memory>
#include <exception>
#include "vector_iterator.hpp"

namespace ft
{

template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef	T											value_type;
	typedef	Alloc										allocator_type;
	typedef	typename allocator_type::reference			reference;
	typedef	typename allocator_type::const_reference	const_refrence;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer		const_pointer;
	typedef	vector_iterator<T>							iterator;
	// typedef	const iterator					const_iterator;
	// typedef	const iterator					const_reverse_iterator;
	typedef	reverse_iterator<iterator>					reverse_iterator;
	typedef	ptrdiff_t									difference_type;
	typedef	size_t										size_type;

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
	void resize (size_type n, value_type val = value_type())
	{
		if (n == _capacity) return;
		if (n < _capacity) {

		}
		if (n > _capacity)
	}

If n is smaller than the current container size, the content is reduced to its first n elements, removing those beyond (and destroying them).

If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n. If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.

If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.

Notice that this function changes the actual content of the container by inserting or erasing elements from it.

Parameters
n
New container size, expressed in number of elements.
Member type size_type is an unsigned integral type.
val
Object whose content is copied to the added elements in case that n is greater than the current container size.
If not specified, the default constructor is used instead.
Member type value_type is the type of the elements in the container, defined in vector as an alias of the first template parameter (T).

Return Value
none

If a reallocation happens, the storage is allocated using the containers allocator, which may throw exceptions on failure (for the default allocator, bad_alloc is thrown if the allocation request does not succeed).


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
	iterator insert( iterator pos, const value_type& value )
	{
		insert(pos, 1, value);
	}

	void insert( iterator pos, size_type count, const value_type& value )
	{
		if (count = 0) return;
		pointer		arr = _data;
		size_type	to_pos = &(*pos) - _data;
		if (_capacity < _size + count) {
			arr = _alloc.allocate(_size + count + 1);
			for (size_type i = 0; i < to_pos; ++i) {
				_alloc.construct(arr + i, *(_data + i));
				_alloc.destory(_data + i);
			}
			for (size_type i = 0; i < (_size - to_pos); ++i) {
				_alloc.construct((arr + to_pos + count + i), *(_data + to_pos + i));
				_alloc.destory(_data + to_pos + i);
			}
			_alloc.deallocate(_data, _capacity);
			_capacity = _size + count + 1;
		} else {
			memmove((arr + to_pos + count), (arr + to_pos), (_size - to_pos));
		}
		for (size_type i = 0; i < count, ++i)
			_alloc.construct((arr + to_pos + i), value);
		_size += count;
	}

	template< class InputIt >
	void insert( iterator pos, InputIt first, InputIt last)
	{
		if (first == last) return;
		size_type	to_pos = &(*pos) - _data;
		size_type	dist = ft::distance(first, last);
		pointer		arr = _data;
		if (_capacity < _size + dist) {
			arr = _alloc.allocate(_size + dist + 1);
			for (size_type i = 0; i < to_pos; ++i) {
				_alloc.construct((arr + i), *(_data + i));
				_alloc.destroy(_data + i);
			}
			for (size_type i = 0; i < (_size - to_pos); ++i) {
				_alloc.construct((arr + to_pos + dist + i), *(_data + to_pos + i));
				_alloc.destory(_data + to_pos + i);
			}
			_alloc.deallocate(_data, _capacity);
			_capacity = _size + dist + 1;
		} else {
			memmove((arr + to_pos + dist), (arr + to_pos), (_size - to_pos));
		}
		for (size_type i = 0; first == last; ++first, ++i)
			_alloc.construct((arr + to_pos + i), *first);
		_size += dist;
	}

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
		memset(this->end() - (last - first), 0, sizeof(value_type) * (last - first));
		return first;
	}

// swap
// Swap content (public member function )
	void clear()
	{
		erase(this->begin(), this->end());
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
	size_type			_capacity;
	size_type			_size;
	allocator_type		_alloc;
	pointer				_data;

	// void	_move_datas(iterator pos, size_type size, difference_type length)
	// {
	// 	if (size == 0 || length == 0)
	// 		return;



	// 	for(iterator it = first; it != last; ++it)
	// 		_alloc.construct(&*(it + (last - first)));

	// }

};


}

#endif
