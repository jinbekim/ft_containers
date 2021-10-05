#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "iterator.hpp"
#include "utils.hpp"
#include <memory>

namespace ft
{

template <typename T, typename Compare, typename Alloc = std::allocator<T> >
class red_black_tree
{
private:
	typedef	red_black_tree										rbtree;
	typedef	ft::tree_node<T>									node_type;
	typedef	ft::tree_node<T>*									node_ptr;
	typedef	typename Alloc::template rebind<node_type>::other	node_alloc_type;
public:

	typedef	T													value_type;
	typedef	Compare												value_compare;
	typedef	Alloc												allocate_type;
	typedef	size_t												size_type;
	typedef	ptrdiff_t											difference_type;
	typedef	typename allocator_type::reference					reference;
	typedef	typename allocator_type::const_reference			const_reference;
	typedef	typename allocator_type::pointer					pointer;
	typedef	typename allocator_type::const_pointer				const_pointer;
	typedef	ft::tree_iterator<Node, Compare>					iterator;
	typedef	ft::tree_const_iterator<Node, Compare>				const_iterator;
	typedef	reverse_iterator<iterator>							reverse_iterator;
	typedef	reverse_iterator<const_iterator>					const_reverse_iterator;


	red_black_tree()
	:
		_root(my_nullptr),
		_node_alloc(),
		_comp()
	{}
	red_black_tree(const red_black_tree &ref)
	:
		_root(ref._root),
		_node_alloc(ref._node_alloc),
		_comp(ref._comp)
	{}
	~red_black_tree() {}
	red_black_tree& operator=(const red_black_tree &ref)
	{
		this->_root = ref._root;
		this->_node_alloc = ref._node_alloc;
		this->_comp = ref._comp;
	}

private:
	node_ptr		_root;
	node_alloc_type	_node_alloc;
	value_compare	_comp;

	void	rotateLeft(node_ptr node)
	{
		node_ptr	rightChild = node->right;
		if (rightChild == my_nullptr)
			return;
		node->right = rightChild->left;
		if (node->right != my_nullptr)
			node->right->parent = node;
		rightChild->parent = node->parent;
		if (node->parent == my_nullptr)
			_root = rightChild;
		else if (node == node->parent->left)
			node->parent->left = rightChild;
		else
			node->parent->right = rightChild;
		rightChild->left = node;
		node->parent = rightChild;
	}
	void	rotateRight(node_ptr node)
	{
		node_ptr	leftChild = node->left;
		if (leftChild == my_nullptr)
			return;
		node->left = leftChild->right;
		if (node->left != my_nullptr)
			node->left->parent = node;
		leftChild->parent = node->parent;
		if (node->parent == my_nullptr)
			_root = leftChild;
		else if (node == node->parent->left)
			node->parent->left = leftChild;
		else
			node->parent->right = leftChild;
		leftChild->right = node;
		node->parent = leftChild;
	}
	node_ptr	getParent(node_ptr node)
	{
		return (node->parent);
	}
	node_ptr	getGrandparent(node_ptr node)
	{
		node_ptr pr = getParent(node);
		if (pr == my_nullptr)
			return (my_nullptr);
		return (getParent(pr));
	}
	node_ptr	getSibling(node_ptr node)
	{
		node_ptr	pr = getParent(node);
		if (pr == my_nullptr)
			return (my_nullptr);
		if (node == pr->left)
			return (pr->right);
		return (pr->right);
	}
	node_ptr	getUncle(node_ptr node)
	{
		node_ptr	pr = getParent(node);
		if (pr == my_nullptr)
			return (my_nullptr);
		return (getSibling(pr));
	}
	Color	getColor(node_ptr node)
	{
		if (node == my_nullptr)
			return (BLACK);
		return (node->color);
	}
	void	setColor(node_ptr node, Color color)
	{
		if (node == my_nullptr)
			return;
		node->color = color;
	}
	void	insertValue(value_type val)
	{
		node_ptr	node = _node_alloc.allocate(1);
		_node_alloc.construct(node->value, tree_node(val));
		_root = insertNode(_root, node);
		fixAfterInsert(node);
	}
	node_ptr	insertNode(node_ptr root, node_ptr node)
	{
		if (root == my_nullptr)
			return (node);
		if (root->value > node->value)
		{
			root->left = insertNode(root->left, node);
			root->left->parent = root;
		} else if (root->value < node->value)
		{
			root->right = insertNode(root->right, node);
			root->right->parent = root;
		}
		return (root);
	}
	void	fixAfterInsert(node_ptr node)
	{
		node_ptr	parent, grandparent;

		while (node != this->_root && getColor(node) == RED && getColor(node->parent) == RED)
		{
			parent = getParent(node);
			grandparent = getGrandparent(node);
			if (grandparent == my_nullptr)
				break;
			node_ptr	uncle = getUncle(node);
			if (getColor(uncle) == RED) { // 삼촌이 red인 경우, 반복.
				setColor(parent, BLACK);
				setColor(uncle, BLACK);
				setColor(grandparent, RED);
				node = grandparent;
			} else if (parent == grandparent->left) { // 삼촌이 black, 종료
				if (node == parent->right) {
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);
				std::swap(parent->color, grandparent->color);
				node = parent;
			} else if (parent == grandparent->right) { // 삼촌이 black, 종료
				if (node == parent->left) {
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandparent);
				std::swap(parent->color, grandparent->color);
				node = parent;
			}
		}
		setColor(_root, BLACK);
	}
	node_ptr	minValueNode(node_ptr node)
	{
		if (node == my_nullptr)
			return (node);
		while (node->left != my_nullptr)
			node = node->left;
		return (node);
	}
	node_ptr	maxValueNode(node_ptr node)
	{
		if (node == my_nullptr)
			return (node);
		while (node->right != my_nullptr)
			node = node->right;
		return (node);
	}
	void	deleteValue(value_type val)
	{
		node_ptr node = findNode(_root, val);
		node_ptr child = node->right;
		if (child == my_nullptr)
			child = node->left;
		if(child != my_nullptr)
			child->parent = node->parent;
		if (getColor(node) == BLACK) {
			if (getColor(child) == RED)
				setColor(child, BLACK);
			else
				delete_case1(child);
		}
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
	}
	node_ptr	findNode(node_ptr node, value_type val)
	{
		if (node == my_nullptr)
			return node;
		if (node->value < val)
			return findNode(node->right, val);
		if (node->value > val)
			return findNode(node->left, val);
		if (node->left == my_nullptr || node->right == my_nullptr)
			return node;
		node_ptr tmp = minValueNode(node->right);
		node->value = tmp->value;
		return findNode(node->right, tmp->value);
	}
	void	delete_case1(node_ptr node)
	{
		if (node->parent != my_nullptr)
			delete_case2(node);
	}
	void	delete_case2(node_ptr node)
	{
		node_ptr sibling = getSibling(node);
		if (getColor(sibling) == RED) {
			std::swap(node->parent->color, sibling->color);
			if (node->parent->left == node)
				rotateLeft(node->parent);
			else
				rotateRight(node->parent);
		}
		delete_case3(node);
	}
	void	delete_case3(node_ptr node)
	{
		node_ptr sibling = getSibling(node);
		if (getColor(node->parent) == BLACK &&
			getColor(sibling) == BLACK &&
			getColor(sibling->left) == BLACK &&
			getColor(sibling->right) == BLACK) {
			setColor(sibling, RED);
			delete_case1(node->parent);
		} else {
			delete_case4(node);
		}
	}
	void	delete_case4(node_ptr node)
	{
		node_ptr sibling = getSibling(node);
		if (getColor(node->parent) == RED &&
			getColor(sibling) == BLACK &&
			getColor(sibling->left) == BLACK &&
			getColor(sibling->right) == BLACK) {
			setColor(sibling, RED);
			setColor(node->parent, BLACK);
		} else {
			delete_case5(node);
		}
	}
	void	delete_case5(node_ptr node)
	{
		node_ptr sibling = getSibling(node);
		if (getColor(sibling) == BLACK) {
			if (node == node->parent->left &&
				getColor(sibling->right) == BLACK &&
				getColor(sibling->left) == RED) {
				std::swap(sibling->color, sibling->left->color);
				rotateRight(sibling);
			} else if (node == node->parent->right &&
				getColor(sibling->left) == BLACK &&
				getColor(sibling->right) == RED) {
				std::swap(sibling->color, sibling->right->color);
				rotateLeft(sibling);
			}
		}
		delete_case6(node);
	}
	void	delete_case6(node_ptr node)
	{
		node_ptr sibling = getSibling(node);
		setColor(sibling, node->parent->color);
		setColor(node->parent, BLACK);
		if (node == node->parent->left) {
			setColor(sibling->right, BLACK);
			rotateLeft(node->parent);
		} else {
			setColor(sibling->left, BLACK);
			rotateRight(node->parent);
		}
	}
};
}
#endif
