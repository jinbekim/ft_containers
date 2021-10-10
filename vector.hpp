#ifndef FT_VECTOR_H
#define FT_VECTOR_H

#include <memory>
#include "utils.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

template<typename T, typename Alloc = std::allocator<T> >
class vector
{
public:
	typedef	T														value_type;
	typedef	Alloc													allocator_type;
	typedef	typename allocator_type::reference						reference;
	typedef	typename allocator_type::const_reference				const_reference;
	typedef	typename allocator_type::pointer						pointer;
	typedef	typename allocator_type::const_pointer					const_pointer;
	typedef	typename allocator_type::size_type						size_type;
	typedef	ft::random_access_iterator<value_type>					iterator;
	typedef	ft::random_access_iterator<const value_type>			const_iterator;
	typedef	ft::reverse_iterator<iterator>							reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;

// default (1)
	explicit vector (const allocator_type& alloc = allocator_type())
	:
		_alloc(alloc),
		_start(my_nullptr),
		_end(my_nullptr),
		_end_capa(my_nullptr)
	{}
// fill (2)
	explicit vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	:
		_alloc(alloc),
		_start(my_nullptr),
		_end(my_nullptr),
		_end_capa(my_nullptr)
	{
		_start = _alloc.allocate(n);
		_end_capa = _start + n;
		_end = _start;
		while (n--)
		{
			_alloc.construct(_end, val);
			_end++;
		}
	}
// range (3)
template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = my_nullptr)
	:
		_alloc(alloc),
		_start(my_nullptr),
		_end(my_nullptr),
		_end_capa(my_nullptr)
	{
		insert(_start, first, last);
	}
// copy (4)
	vector (const vector& x)
	:
		_alloc(x._alloc),
		_start(my_nullptr),
		_end(my_nullptr),
		_end_capa(my_nullptr)
	{
		insert(_start, x.begin(), x.end());
	}
	~vector()
	{
		this->clear();
		_alloc.deallocate(_start, this->capacity());
	}
	vector& operator=(const vector& x)
	{
		if(this == &x)
			return (*this);
		this->clear();
		insert(_start, x.begin(), x.end());
		return (*this);
	}

// Iterators:
	iterator				begin()			{ return _start; }
	const_iterator			begin()	 const	{ return _start; }
	iterator				end()			{ return _end; }
	const_iterator			end()	 const	{ return _end; }
	reverse_iterator		rbegin()		{ return reverse_iterator(_end); }
	const_reverse_iterator	rbegin() const	{ return reverse_iterator(_end); }
	reverse_iterator		rend()			{ return reverse_iterator(_start); }
	const_reverse_iterator	rend()	 const	{ return reverse_iterator(_start); }

// Capacity:
	size_type	size()		const	{ return (_end - _start); }
	size_type	max_size()	const	{ return _alloc.max_size(); }
	void		resize (size_type n, value_type val = value_type())
	{
		if (n > this->max_size())
			throw (std::length_error("vector::resize"));
		if (this->size() == n) return;
		if (this->size() > n)
		{
			while (_start + n != _end)
				_alloc.destroy(--_end);
		}
		if (this->size() < n)
			this->insert(_end, n - this->size(), val);
	}
	size_type	capacity()	const	{ return (_end_capa - _start); }
	bool		empty()		const	{ return (_end == _start); }
	void		reserve(size_type n)
	{
		if (n > this->max_size())
			throw (std::length_error("vector::reserve"));
		if (this->capacity() < n)
		{
			pointer	prev = this->_start;
			pointer	prev_end = this->_end;
			size_type prev_size = this->size();
			size_type size = this->capacity();
			_start = _alloc.allocate(n);
			_end_capa = _start + n;
			_end = _start;
			while (prev != prev_end)
			{
				_alloc.construct(_end, *prev);
				_alloc.destroy(prev);
				++_end;
				++prev;
			}
			_alloc.deallocate(prev - prev_size, size);
		}
	}

// Element access:
	reference			operator[] (size_type n) { return (*(this->_start + n)); }
	const_reference		operator[] (size_type n) const { return (*(this->_start + n)); }
	reference			at (size_type n)
	{
		if (n >= this->size())
			throw std::out_of_range("vector::at");
		return ((*this)[n]);
	}
	const_reference		at (size_type n) const
	{
		if (n >= this->size())
			throw std::out_of_range("vector::at");
		return ((*this)[n]);
	}

	reference		front() { return (*(_start)); }
	reference		back() { return (*(_end - 1)); }
	const_reference	front() const { return (*(_start)); }
	const_reference	back() const { return (*(_end - 1)); }

// Modifiers:
template <class InputIterator>
	void	assign (InputIterator first, InputIterator last,
	typename ft::enable_if<!is_integral<InputIterator>::value>::type* = my_nullptr)
	{
		// if (!ft::is_input_iter<ft::iterator_traits<InputIterator>::iterator_category>::value)
		this->clear();
		size_type	size = ft::distance(first, last);
		if (size <= this->capacity())
			for (; &*first != &*last; ++first, ++_end)
				_alloc.construct(_end, *first);
		else
		{
			this->reserve(size);
			for (; &*first != &*last; ++first, ++_end)
				_alloc.construct(_end, *first);
		}
	}
	void assign (size_type n, const value_type& val)
	{
		this->clear();
		if (this->capacity() < n)
		{
			this->reserve(n);
			while (n--)
				_alloc.construct(_end++, val);
		}
		else
			while (n--)
				_alloc.construct(_end++, val);
	}
	void	push_back (const value_type& val)
	{
		if (_end == _end_capa)
		{
			size_type	size = this->size();
			if (size == 0)
				size = 1;
			else
				size *= 2;
			this->reserve(size);
		}
		_alloc.construct(_end++, val);
	}
	void	pop_back()
	{
		if (this->size())
			_alloc.destroy(--_end);
	}
	iterator insert (iterator position, const value_type& val)
	{
		size_type	rpos = _end - &(*position);
		size_type	pos = &(*position) - _start;
		if (this->size() == 0)
			this->reserve(1);
		else if (_end == _end_capa)
			this->reserve(this->size() * 2);
		for (size_type i = 0; i < rpos; ++i)
		{
			_alloc.construct(_end - i, *(_end - i - 1));
			_alloc.destroy(_end - i - 1);
		}
		_alloc.construct(_start + pos, val);
		_end++;
		return (iterator(_start + pos));
	}
	void insert (iterator position, size_type n, const value_type& val)
	{
		if (position > this->end() || position < this->begin())
			return;
		size_type	nec_size = n + this->size();
		size_type	prev_capa = this->capacity();
		size_type	pos = &*position - _start;
		pointer		new_start = my_nullptr;
		if (this->max_size() < nec_size)
			throw (std::length_error("vector::insert (fill)"));
		if (this->capacity() * 2 < nec_size) {
			new_start = _alloc.allocate(nec_size);
			_end_capa = new_start + nec_size;
		}
		else {
			new_start = _alloc.allocate(this->capacity() * 2);
			_end_capa = new_start + this->capacity() * 2;
		}
		for (size_type i = 0; i < pos; ++i)
			_alloc.construct(new_start + i, *(_start + i));
		for (size_type i = 0; i < n; ++i)
			_alloc.construct(new_start + pos + i, val);
		for (size_type i = 0; i < this->size() - pos; ++i)
			_alloc.construct(new_start + pos + n + i, *(_start + pos + i));
		for (size_type i = 0; i < this->size(); ++i)
			_alloc.destroy(_start + i);
		_alloc.deallocate(_start, prev_capa);
		_end = new_start + n + this->size();
		_start = new_start;
	}
template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
	typename ft::enable_if<!is_integral<InputIterator>::value>::type* = my_nullptr)
	{
		if (position > this->end() || position < this->begin())
			return;
		size_type	num = ft::distance(first, last);
		size_type	nec_size = num + this->size();
		size_type	prev_capa = this->capacity();
		size_type	pos = &*position - _start;
		pointer		new_start = my_nullptr;
		if (this->max_size() < nec_size)
			throw (std::length_error("vector::insert (range)"));
		if (this->capacity() * 2 < nec_size) {
			new_start = _alloc.allocate(nec_size);
			_end_capa = new_start + nec_size;
		}
		else {
			new_start = _alloc.allocate(this->capacity() * 2);
			_end_capa = new_start + this->capacity() * 2;
		}
		for (size_type i = 0; i < pos; ++i)
			_alloc.construct(new_start + i, *(_start + i));
		for (size_type i = 0; i < num; ++i)
			_alloc.construct(new_start + pos + i, *(&*first++));
		for (size_type i = 0; i < this->size() - pos; ++i)
			_alloc.construct(new_start + pos + num + i, *(_start + pos + i));
		for (size_type i = 0; i < this->size(); ++i)
			_alloc.destroy(_start + i);
		_alloc.deallocate(_start, prev_capa);
		_end = new_start + num + this->size();
		_start = new_start;
	}
	iterator erase( iterator pos ) { return erase(pos, pos + 1); }
	iterator erase( iterator first, iterator last )
	{
		pointer	prev_first = &*first;
		for (; first != last; ++first)
			_alloc.destroy(&*first);
		for (int i = 0; &*last + i != _end; ++i)
		{
			_alloc.construct(prev_first + i, *(&*last + i));
			_alloc.destroy(&*last + i);
		}
		_end -= (&*first - prev_first);
		return prev_first;
	}
	void swap (vector& x)
	{
		if (&x == this)
			return;
		pointer	tmp_start = x._start;
		pointer	tmp_end = x._end;
		pointer	tmp_end_capa = x._end_capa;
		allocator_type	tmp_alloc = x._alloc;

		x._start = this->_start;
		x._end_capa = this->_end_capa;
		x._end = this->_end;
		x._alloc = this->_alloc;

		this->_start = tmp_start;
		this->_end_capa = tmp_end_capa;
		this->_end = tmp_end;
		this->_alloc = tmp_alloc;
	}
	void clear()
	{
		while (_end != _start)
			_alloc.destroy(--_end);
	}

// Allocator:
	allocator_type get_allocator() const
	{
		return allocator_type();
	}

protected:
	allocator_type		_alloc;
	pointer				_start;
	pointer				_end;
	pointer				_end_capa;

};

template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::vector<T>::const_iterator first1 = lhs.begin();
		typename ft::vector<T>::const_iterator first2 = rhs.begin();

		while (first1 != lhs.end())
		{
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return (true);
	}
template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs == rhs); }
template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
	}
template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(rhs < lhs); }
template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); }
template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); }

template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif
