#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "utils.hpp"
#include "iterator.hpp"

namespace ft
{


template <typename T>
class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
private:
	typedef	ft::tree_node<T>														node;
	typedef	ft::tree_node<T>*														node_pointer;
public:
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::pointer			pointer;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::reference			reference;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::value_type		value_type;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;

	tree_iterator()
	:
		_node(my_nullptr),
		_end_node(my_nullptr)
	{}
	tree_iterator(const tree_iterator &ref)
	:
		_node(ref._node),
		_end_node(ref._end_node)
	{}
	tree_iterator(node_pointer node, node_pointer end_node)
	:
		_node(node),
		_end_node(end_node)
	{}
	virtual ~tree_iterator() {}
	tree_iterator&		operator=(const tree_iterator& ref)
	{
		if (this != &ref) {
			this->_node = ref._node;
			this->_end_node = ref._end_node;
		}
		return (*this);
	}

	// pointer				base() const { return (this->_node);

	tree_iterator&		operator++()
	{
		if (_node->right != my_nullptr) {
			_node = minValueNode(_node->right);
			return (*this);
		}
		while (getParent(_node) && getParent(_node)->left != _node)
			_node = _node->parent;
		if (getParent(_node))
			_node = _node->parent;
		else
			return (_end_node);
		return (*this);
	}
	tree_iterator&		operator--()
	{
		if (_node->left != my_nullptr) {
			_node = maxValueNode(_node->left);
			return (*this);
		}
		while (getParent(_node) && getParent(_node)->right != _node)
			_node = _node->parent;
		if (getParent(_node))
			_node = _node->parent;
		else
			_node = my_nullptr;
		return (*this);
	}
	tree_iterator		operator++(int)		{ tree_iterator	itr = (*this); ++_node; return (itr); }
	tree_iterator		operator--(int)		{ tree_iterator	itr = (*this); --_node; return (itr); }
	reference			operator*()	const	{ return (_node->value); }
	pointer				operator->()		{ return (&(_node->value)); }
	bool				operator ==	(const tree_iterator& lhs) { return (this->_node == lhs._node); }
	bool				operator !=	(const tree_iterator& lhs) { return (this->_node != lhs._node); }

private:
	node_pointer	_node;
	node_pointer	_end_node;

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
