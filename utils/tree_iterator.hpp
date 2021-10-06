#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "utils.hpp"

namespace ft
{


template <typename T>
class tree_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
{
private:
	typedef	red_black_tree<T>														node;
	typedef	node*																	node_pointer;
public:
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::iterator_category	iterator_category;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::pointer			pointer;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::reference			reference;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::value_type		value_type;
	typedef	typename ft::iterator<bidirectional_iterator_tag, T>::difference_type	difference_type;

	tree_iterator() : _node(my_nullptr) {}
	tree_iterator(const tree_iterator &ref) : _node(ref._node) {}
	tree_iterator(pointer ptr) : _node(ptr) {}
	virtual ~tree_iterator() {}

	tree_iterator&		operator=(const tree_iterator& ref)
	{
		if (this != &ref)
			this->_node = ref._node;
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
	tree_iterator		operator--(int)		{ tree_iterator	itr = (*this); --_node; return (itr); }
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
		return (*this);
	}
	tree_iterator		operator++(int)		{ tree_iterator	itr = (*this); ++_node; return (itr); }
	reference			operator*()	const	{ return (_node->value); }
	pointer				operator->()		{ return (&_node->value); }
	bool	operator ==	(const tree_iterator& lhs) { return (this->_node == lhs._node); }
	bool	operator !=	(const tree_iterator& lhs) { return (this->_node != lhs._node); }



private:
	node_pointer	_node;

template	<typename value_type, typename, typename>
	friend class RedBlackTree;
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
	node_pointer	getParent(node_pointer node)
	{
		return (node->parent);
	}
	node_pointer	getGrandparent(node_pointer node)
	{
		node_pointer pr = getParent(node);
		if (pr == my_nullptr)
			return (my_nullptr);
		return (getParent(pr));
	}
	node_pointer	getSibling(node_pointer node)
	{
		node_pointer	pr = getParent(node);
		if (pr == my_nullptr)
			return (my_nullptr);
		if (node == pr->left)
			return (pr->right);
		return (pr->right);
	}
	node_pointer	getUncle(node_pointer node)
	{
		node_pointer	pr = getParent(node);
		if (pr == my_nullptr)
			return (my_nullptr);
		return (getSibling(pr));
	}
	Color	getColor(node_pointer node)
	{
		if (node == my_nullptr)
			return (BLACK);
		return (node->color);
	}
	void	setColor(node_pointer node, Color color)
	{
		if (node == my_nullptr)
			return;
		node->color = color;
	}
};


}
#endif
