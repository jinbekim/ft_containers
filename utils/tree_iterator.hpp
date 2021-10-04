#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{


template <typename T, typename Compare>
class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:

	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::pointer			pointer;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::reference			reference;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::value_type		value_type;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;

	tree_iterator() : _ptr(my_nullptr) {}
	tree_iterator(const tree_iterator &ref) : _ptr(ref._ptr) {}
	tree_iterator(pointer ptr) : _ptr(ptr) {}
	virtual ~tree_iterator() {}

	tree_iterator&	operator=(const tree_iterator& ref)
	{
		if (this != &ref)
			this->_ptr = ref._ptr;
		return (*this);
	}

	pointer					base() const { return (this->_ptr); }

private:
	pointer	_ptr;
};

}
#endif
