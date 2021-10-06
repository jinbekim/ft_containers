#ifndef RED_BLACK_TREE_HPP
#define RED_BLACK_TREE_HPP

#include "tree_iterator.hpp"
#include "reverse_iterator.hpp"
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
	typedef	ft::tree_node<T>*									node_pointer;
	typedef	typename Alloc::template rebind<node_type>::other	node_alloc_type;
public:

	typedef	T													value_type;
	typedef	Compare												value_compare;
	typedef	Alloc												allocate_type;
	typedef	size_t												size_type;
	typedef	ptrdiff_t											difference_type;
	typedef	typename allocate_type::reference					reference;
	typedef	typename allocate_type::const_reference				const_reference;
	typedef	typename allocate_type::pointer						pointer;
	typedef	typename allocate_type::const_pointer				const_pointer;
	typedef	ft::tree_iterator<value_type>						iterator;
	typedef	ft::tree_iterator<const value_type>					const_iterator;
	typedef	ft::reverse_iterator<iterator>							reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>					const_reverse_iterator;


	red_black_tree()
	:
		_root(my_nullptr),
		_node_alloc(node_alloc_type()),
		_comp(value_compare()),
		_end_node(my_nullptr),
		_size(0)
	{
		this->_end_node = _node_alloc.allocate(1);
		_node_alloc.construct(_end_node, node_type());
	}
	red_black_tree(const red_black_tree &ref)
	:
		_root(ref._root),
		_node_alloc(ref._node_alloc),
		_comp(ref._comp),
		_end_node(ref._end_node),
		_size(ref._size)
	{}
	~red_black_tree()
	{
		this->clear();
		_node_alloc.destroy(_end_node);
		_node_alloc.deallocate(_end_node, 1);
	}
	red_black_tree& operator=(const red_black_tree &ref)
	{
		this->_root = ref._root;
		this->_node_alloc = ref._node_alloc;
		this->_comp = ref._comp;
		this->_end_node = ref._end_node;
		this->_size = ref._size;
	}
// Iterators:
	iterator				begin(){ return (iterator(minValueNode(_root), _end_node)); }
	const_iterator			begin() const  { return (const_iterator(minValueNode(_root), _end_node)); }
	iterator				end() { return (iterator(_end_node, _end_node)); }
	const_iterator			end() const { return (const_iterator(_end_node, _end_node)); }
	reverse_iterator		rbegin() { return (reverse_iterator(begin())); }
	const_reverse_iterator	rbegin() const { return (const_reverse_iterator(begin())); }
	reverse_iterator		rend() { return (reverse_iterator(end())); }
	const_reverse_iterator	rend() const { return (const_reverse_iterator(end())); }
// Capacity:
	bool					empty() const { return (this->_size == 0); }
	size_type				size() const { return (this->_size); }
	size_type				max_size() const { return (_node_alloc.max_size()); }
// Modifiers:
	pair<iterator,bool>		insert (const value_type& val)
	{ return (insertValue(val)); }
	iterator				insert (iterator position, const value_type& val)
	{
		(void)position;
		return (insertValue(val)->first);
	}
template <class InputIterator>
	void					insert (InputIterator first, InputIterator last)
	{
		while (first != last) {
			this->insert(first->value);
			++first;
		}
	}
	void					erase (iterator position) { return (deleteValue(*position)); }
	size_type				erase (const value_type& k) { return (deleteValue(k)); }
	void					erase (iterator first, iterator last)
	{
		for (iterator it = first; first != last; ++it)
			erase(it);
	}
	void swap (rbtree& x)
	{
		if (this == &x)
			return;
		node_pointer	tmp_root = x._root;
		node_alloc_type	tmp_node_alloc = x._node_alloc;
		value_compare	tmp_comp = x._comp;
		node_pointer	tmp_end_node = x._end_node;
		size_type		tmp_size = x._size;

		x._root = this->_root;
		x._node_alloc = this->_node_alloc;
		x._comp = this->_comp;
		x._end_node = this->_end_node;
		x._size = this->_size;

		this->_root = tmp_root;
		this->_node_alloc = tmp_node_alloc;
		this->_comp = tmp_comp;
		this->_end_node = tmp_end_node;
		this->_size = tmp_size;
	}
	void clear()
	{
		deleteTree(_root);
		this->_root = my_nullptr;
		this->_size = 0;
	}
	iterator	find (const value_type& k)
	{
		node_pointer	tmp = this->_root;
		while (tmp != my_nullptr) {
			if (tmp->value->first == k.first)
				break;
			else if (_comp(tmp->value->first, k.first))
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		if (tmp == my_nullptr)
			return (iterator(this->_end_node, this->_end_node));
		return (iterator(tmp, this->_end_node));
	}
	size_type	count (const value_type& k) const
	{
		iterator	tmp = find(k);
		if (tmp->_end_node == tmp->_node)
			return (0);
		size_type	count = 0;
		for (iterator it = tmp; it != _end_node; ++it) {
			if (it->first == k.first)
				++count;
		}
		return (count);
	}

private:
	node_pointer	_root;
	node_alloc_type	_node_alloc;
	value_compare	_comp;
	node_pointer	_end_node;
	size_type		_size;


	void	deleteTree(node_pointer node)
	{
		if (node == my_nullptr)
			return;
		deleteTree(node->left);
		deleteTree(node->right);
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
	}

	void	rotateLeft(node_pointer node)
	{
		node_pointer	rightChild = node->right;
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
	void	rotateRight(node_pointer node)
	{
		node_pointer	leftChild = node->left;
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
	pair<iterator,bool>	insertValue(value_type val)
	{
		node_pointer	node = _node_alloc.allocate(1);
		_node_alloc.construct(node->value, node_type(val));
		pair<iterator,bool> ret = insertNode(node);
		if (ret->second == false) {
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		} else {
			this->_size++;
			fixAfterInsert(node);
		}
		return (ret);
	}
	pair<iterator,bool>	insertNode(node_pointer node)
	{
		node_pointer tmp = _root;
		if (_root == my_nullptr) {
			this->_root = node;
			return (ft::make_pair(iterator(node, _end_node), true));
		}
		while (tmp) {
			if (_comp(tmp->value, node->value))
				tmp = tmp->right;
			else if (_comp(node->value, tmp->value))
				tmp = tmp->left;
			else
				return (ft::make_pair(iterator(tmp, _end_node), false));
		}
		if (_comp(getParent(tmp)->value, node->value))
			tmp->parent->right = node;
		else
			tmp->parent->left = node;
		return (ft::make_pair(iterator(node, _end_node), true));
	}
	void	fixAfterInsert(node_pointer node)
	{
		node_pointer	parent, grandparent;

		while (node != this->_root && getColor(node) == RED && getColor(node->parent) == RED)
		{
			parent = getParent(node);
			grandparent = getGrandparent(node);
			if (grandparent == my_nullptr)
				break;
			node_pointer	uncle = getUncle(node);
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
	void	deleteValue(value_type val)
	{
		node_pointer node = findNode(_root, val);
		if (node == my_nullptr)
			return;
		node_pointer child = node->right;
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
		this->_size--;
	}
	node_pointer	findNode(node_pointer node, value_type val)
	{
		if (node == my_nullptr)
			return node;
		if (_comp(node->value, val))
			return findNode(node->right, val);
		if (_comp(val, node->value))
			return findNode(node->left, val);
		if (node->left == my_nullptr || node->right == my_nullptr)
			return node;
		node_pointer tmp = minValueNode(node->right);
		node->value = tmp->value;
		return findNode(node->right, tmp->value);
	}
	void	delete_case1(node_pointer node)
	{
		if (node->parent != my_nullptr)
			delete_case2(node);
	}
	void	delete_case2(node_pointer node)
	{
		node_pointer sibling = getSibling(node);
		if (getColor(sibling) == RED) {
			std::swap(node->parent->color, sibling->color);
			if (node->parent->left == node)
				rotateLeft(node->parent);
			else
				rotateRight(node->parent);
		}
		delete_case3(node);
	}
	void	delete_case3(node_pointer node)
	{
		node_pointer sibling = getSibling(node);
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
	void	delete_case4(node_pointer node)
	{
		node_pointer sibling = getSibling(node);
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
	void	delete_case5(node_pointer node)
	{
		node_pointer sibling = getSibling(node);
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
	void	delete_case6(node_pointer node)
	{
		node_pointer sibling = getSibling(node);
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
