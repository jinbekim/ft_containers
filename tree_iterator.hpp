#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "utils.hpp"
#include "iterator.hpp"

namespace ft
{
template <typename T>
class tree_const_iterator;

template <typename T>
class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
private:
	typedef	ft::tree_node<T>				node;
	typedef	ft::tree_node<T>*				node_pointer;
public:
	typedef	bidirectional_iterator_tag		iterator_category;
	typedef	T								value_type;
	typedef	value_type&						reference;
	typedef	std::ptrdiff_t					difference_type;
	typedef	T*								pointer;

	tree_iterator()
	:
		_node(my_nullptr)
	{}
	tree_iterator(const tree_iterator &ref)
	:
		_node(ref._node)
	{}
	tree_iterator(node_pointer node)
	:
		_node(node)
	{}
	virtual ~tree_iterator() {}
	tree_iterator&		operator=(const tree_iterator& ref)
	{
		if (this != &ref)
			this->_node = ref._node;
		return (*this);
	}

	node_pointer		base() const { return (this->_node); }

	tree_iterator&		operator++()
	{
		if (_node->right != my_nullptr) {
			_node = minValueNode(_node->right);
			return (*this);
		}
		while (_node->parent && _node->parent->left != _node)
			_node = _node->parent;
		if (_node->parent)
			_node = _node->parent;
		return (*this);
	}
	tree_iterator&		operator--()
	{
		if (_node->left != my_nullptr) {
			_node = maxValueNode(_node->left);
			return (*this);
		}
		while (_node->parent && _node->parent->right != _node)
			_node = _node->parent;
		if (_node->parent)
			_node = _node->parent;
		else
			_node = my_nullptr;
		return (*this);
	}
	tree_iterator		operator++(int)		{ tree_iterator	tmp = (*this); ++(*this); return (tmp); }
	tree_iterator		operator--(int)		{ tree_iterator	tmp = (*this); --(*this); return (tmp); }
	reference			operator*()	const	{ return (_node->value); }
	pointer				operator->()	const	{ return (&(_node->value)); }
	bool				operator ==	(const tree_iterator& lhs) { return (this->_node == lhs._node); }
	bool				operator !=	(const tree_iterator& lhs) { return (this->_node != lhs._node); }
	bool				operator ==	(const tree_const_iterator<T>& lhs) { return (this->base() == lhs.base()); }
	bool				operator !=	(const tree_const_iterator<T>& lhs) { return (this->base() != lhs.base()); }

private:
	node_pointer	_node;

	node_pointer	minValueNode(node_pointer node)
	{
		if (node == my_nullptr)
			return (node);
		while (node->left != my_nullptr)
			node = node->left;
		return (node);
	}
	node_pointer	maxValueNode(node_pointer node)
	{
		if (node == my_nullptr)
			return (node);
		while (node->right != my_nullptr)
			node = node->right;
		return (node);
	}

};

template <typename T>
class tree_const_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
private:
	typedef	ft::tree_node<T>				node;
	typedef	ft::tree_node<T>*				node_pointer;
public:
	typedef	bidirectional_iterator_tag		iterator_category;
	typedef	T								value_type;
	typedef	const value_type&				reference;
	typedef	std::ptrdiff_t					difference_type;
	typedef	const T*						pointer;

	tree_const_iterator()
	:
		_node(my_nullptr)
	{}
	tree_const_iterator(const tree_const_iterator &ref)
	:
		_node(ref._node)
	{}
	tree_const_iterator(node_pointer node)
	:
		_node(node)
	{}
	virtual ~tree_const_iterator() {}
	tree_const_iterator&		operator=(const tree_const_iterator& ref)
	{
		if (this != &ref)
			this->_node = ref._node;
		return (*this);
	}
	tree_const_iterator(const tree_iterator<T>& other)
	:
		_node(other.base())
	{}

	node_pointer		base() const { return (this->_node); }

	tree_const_iterator&		operator++()
	{
		if (_node->right != my_nullptr) {
			_node = minValueNode(_node->right);
			return (*this);
		}
		while (_node->parent && _node->parent->left != _node)
			_node = _node->parent;
		if (_node->parent)
			_node = _node->parent;
		return (*this);
	}
	tree_const_iterator&		operator--()
	{
		if (_node->left != my_nullptr) {
			_node = maxValueNode(_node->left);
			return (*this);
		}
		while (_node->parent && _node->parent->right != _node)
			_node = _node->parent;
		if (_node->parent)
			_node = _node->parent;
		else
			_node = my_nullptr;
		return (*this);
	}
	tree_const_iterator		operator++(int)		{ tree_const_iterator	itr = (*this); ++(*this); return (itr); }
	tree_const_iterator		operator--(int)		{ tree_const_iterator	itr = (*this); --(*this); return (itr); }
	reference			operator*()	const	{ return (_node->value); }
	pointer				operator->() const	{ return (&(_node->value)); }
	bool				operator ==	(const tree_const_iterator& lhs) { return (this->_node == lhs._node); }
	bool				operator !=	(const tree_const_iterator& lhs) { return (this->_node != lhs._node); }
	bool				operator ==	(const tree_iterator<T>& lhs) { return (this->base() == lhs.base()); }
	bool				operator !=	(const tree_iterator<T>& lhs) { return (this->base() != lhs.base()); }

private:
	node_pointer	_node;

	node_pointer	minValueNode(node_pointer node)
	{
		if (node == my_nullptr)
			return (node);
		while (node->left != my_nullptr)
			node = node->left;
		return (node);
	}
	node_pointer	maxValueNode(node_pointer node)
	{
		if (node == my_nullptr)
			return (node);
		while (node->right != my_nullptr)
			node = node->right;
		return (node);
	}

};

}
#endif
