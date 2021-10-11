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
	typedef	ft::tree_const_iterator<value_type>					const_iterator;
	typedef	ft::reverse_iterator<iterator>						reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>				const_reverse_iterator;


	red_black_tree(value_compare const& comp, allocate_type const& alloc, node_alloc_type const& node_alloc = node_alloc_type())
	:
		_comp(comp),
		_alloc(alloc),
		_node_alloc(node_alloc),
		_meta_node(my_nullptr),
		_size(0)
	{
		_meta_node = _node_alloc.allocate(1);
		_node_alloc.construct(_meta_node, node_type());
	}
	red_black_tree(const red_black_tree &ref)
	:
		_comp(ref._comp),
		_alloc(ref._alloc),
		_node_alloc(ref._node_alloc),
		_meta_node(my_nullptr),
		_size(0)
	{
		_meta_node = _node_alloc.allocate(1);
		_node_alloc.construct(_meta_node, node_type());
		if (ref.getRoot() != my_nullptr) {
			copyTree(ref.getRoot());
		}
	}
	void	copyTree(node_pointer node)
	{
		if(node != my_nullptr) {
			insertValue(node->value);
			copyTree(node->left);
			copyTree(node->right);
		}
	}
	virtual ~red_black_tree()
	{
		this->clear();
		_node_alloc.destroy(_meta_node);
		_node_alloc.deallocate(_meta_node, 1);
	}
	red_black_tree& operator=(const red_black_tree &ref)
	{
		if (this == &ref)
			return (*this);
		this->clear();
		this->_comp = ref._comp;
		this->_alloc = ref._alloc;
		this->_node_alloc = ref._node_alloc;
		copyTree(ref.getRoot());
		this->_size = ref._size;
		return (*this);
	}
// Iterators:
	iterator				begin(){ return (iterator(minValueNode(_meta_node))); }
	const_iterator			begin() const  { return (const_iterator(minValueNode(_meta_node))); }
	iterator				end() { return (iterator(_meta_node)); }
	const_iterator			end() const { return (const_iterator(_meta_node)); }
	reverse_iterator		rbegin() { return (reverse_iterator(end())); }
	const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
	reverse_iterator		rend() { return (reverse_iterator(begin())); }
	const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
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
		return (insertValue(val).first);
	}
template <class InputIterator>
	void					insert (InputIterator first, InputIterator last)
	{
		while (first != last) {
			this->insert(*first);
			++first;
		}
	}
	void					erase (const_iterator position) { deleteValue(*position); }
	size_type				erase (const value_type& k) { return (deleteValue(k)); }
	void					erase (const_iterator first, const_iterator last)
	{
		for (const_iterator it = first; it != last; ) {
			erase(it++);
		}
	}
	void swap (rbtree& x)
	{
		if (this == &x)
			return;
		value_compare	tmp_comp = x._comp;
		node_alloc_type	tmp_node_alloc = x._node_alloc;
		node_pointer	tmp_meta_node = x._meta_node;
		size_type		tmp_size = x._size;

		x._comp = this->_comp;
		x._node_alloc = this->_node_alloc;
		x._meta_node = this->_meta_node;
		x._size = this->_size;

		this->_comp = tmp_comp;
		this->_node_alloc = tmp_node_alloc;
		this->_meta_node = tmp_meta_node;
		this->_size = tmp_size;
	}
	void clear()
	{
		deleteTree(getRoot());
		setRoot(my_nullptr);
		this->_size = 0;
	}
	iterator	find (const value_type& k) const
	{
		node_pointer	tmp = getRoot();
		while (tmp != my_nullptr) {
			if (!_comp(tmp->value, k) && !_comp(k, tmp->value))
				break;
			else if (_comp(tmp->value, k))
				tmp = tmp->right;
			else
				tmp = tmp->left;
		}
		if (tmp == my_nullptr)
			return (iterator(this->_meta_node));
		return (iterator(tmp));
	}
	size_type	count (const value_type& k) const
	{
		iterator	tmp = find(k);
		if (tmp == end())
			return (0);
		size_type	count = 0;
		for (iterator it = tmp; it != end(); ++it) {
			if (!_comp(*it, k) && !_comp(k, *it))
				++count;
		}
		return (count);
	}

private:
	value_compare	_comp;
	allocate_type	_alloc;
	node_alloc_type	_node_alloc;
	node_pointer	_meta_node;
	size_type		_size;

	node_pointer	getRoot(void) const
	{ return (_meta_node->left); }
	void			setRoot(node_pointer node)
	{
		this->_meta_node->left = node;
		this->_meta_node->right = node;
		if (node != my_nullptr)
			node->parent = _meta_node;
	}
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
		if (getParent(node) == my_nullptr)
			setRoot(rightChild);
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
		if (getParent(node) == my_nullptr)
			setRoot(leftChild);
		else if (node == node->parent->left)
			node->parent->left = leftChild;
		else
			node->parent->right = leftChild;
		leftChild->right = node;
		node->parent = leftChild;
	}
	node_pointer	minValueNode(node_pointer node) const
	{
		if (node == my_nullptr)
			return (node);
		while (node->left != my_nullptr)
			node = node->left;
		return (node);
	}
	node_pointer	maxValueNode(node_pointer node) const
	{
		if (node == my_nullptr)
			return (node);
		while (node->right != my_nullptr)
			node = node->right;
		return (node);
	}
	node_pointer	getParent(node_pointer node) const
	{
		if (node == my_nullptr)
			return node;
		if (node->parent == this->_meta_node)
			return (my_nullptr);
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
		return (pr->left);
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
	pair<iterator,bool>	insertValue(const value_type& val)
	{
		node_pointer	node = _node_alloc.allocate(1);
		_node_alloc.construct(node, node_type(val));
		pair<iterator,bool> ret = insertNode(node);
		if (ret.second == false) {
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
		node_pointer tmp = getRoot();
		node_pointer parent;
		if (tmp == my_nullptr) {
			setRoot(node);
			return (ft::make_pair(iterator(node), true));
		}
		while (tmp) {
			if (_comp(tmp->value, node->value)) {
				parent = tmp;
				tmp = tmp->right;
			}
			else if (_comp(node->value, tmp->value)) {
				parent = tmp;
				tmp = tmp->left;
			}
			else
				return (ft::make_pair(iterator(tmp), false));
		}
		if (_comp(parent->value, node->value)) {
			parent->right = node;
			node->parent = parent;
		}
		else {
			parent->left = node;
			node->parent = parent;
		}
		return (ft::make_pair(iterator(node), true));
	}
	void	insertCase1(node_pointer& node)
	{
		setColor(getParent(node), BLACK);
		setColor(getUncle(node), BLACK);
		setColor(getGrandparent(node), RED);
		node = getGrandparent(node);
	}
	void	insertCase2(node_pointer& node, node_pointer& p)
	{
		if (p == getGrandparent(node)->left) {
			rotateLeft(p);
			node = p;
			p = getParent(node);
		}
		if (p == getGrandparent(node)->right) {
			rotateRight(p);
			node = p;
			p = getParent(node);
		}
	}
	void	insertCase3(node_pointer& node, node_pointer p, node_pointer g)
	{
		if (p == g->left)
			rotateRight(g);
		if (p == g->right)
			rotateLeft(g);
		std::swap(p->color, g->color);
		node = p;
	}

	void	fixAfterInsert(node_pointer node)
	{
		node_pointer	parent, grandparent;

		while (node != getRoot() && getColor(node) == RED && getColor(getParent(node)) == RED)
		{
			parent = getParent(node);
			grandparent = getGrandparent(node);
			if (grandparent == my_nullptr)
				break;
			node_pointer	uncle = getUncle(node);
			if (getColor(uncle) == RED) {
				insertCase1(node);
			} else if (parent == grandparent->left) {
				if (node == parent->right)
					insertCase2(node, parent);
				insertCase3(node, parent, grandparent);
			} else if (parent == grandparent->right) {
				if (node == parent->left)
					insertCase2(node, parent);
				insertCase3(node, parent, grandparent);
			}
		}
		setColor(getRoot(), BLACK);
	}

	size_type	deleteValue(const value_type& val)
	{
		node_pointer target = deleteNode(getRoot(), val);
		if (target == my_nullptr)
			return (0);
		fixAfterDelete(target);
		this->_size--;
		return (1);
	}

	void	deleteRedCase(node_pointer& node)
	{
		node_pointer child = node->left != my_nullptr ? node->left : node->right;
		if (node == node->parent->left)
			node->parent->left = child;
		else
			node->parent->right = child;
		if (child != my_nullptr)
			child->parent = node->parent;
		setColor(child, BLACK);
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
	}
	void	deleteRootCase(node_pointer root)
	{
		if (root->right)
			setRoot(root->right);
		else
			setRoot(root->left);
		_node_alloc.destroy(root);
		_node_alloc.deallocate(root, 1);
		setColor(getRoot(), BLACK);
		return;

	}
	void	deleteCase1(node_pointer& s, node_pointer& p)
	{
		setColor(s, BLACK);
		setColor(p, RED);
		if (s == p->right)
			rotateLeft(p);
		if (s == p->left)
			rotateRight(p);
	}
	void	deleteCase2(node_pointer s, node_pointer p, node_pointer& node)
	{
		setColor(s, RED);
		if (getColor(p) == RED)
			setColor(p, BLACK);
		else
			setColor(p, DBLACK);
		node = p;
	}
	void	deleteCase3(node_pointer& s, node_pointer& p)
	{
		if (s == p->right) {
			setColor(s->left, BLACK);
			setColor(s, RED);
			rotateRight(s);
			s = p->right;
		}
		if (s == p->left) {
			setColor(s->right, BLACK);
			setColor(s, RED);
			rotateLeft(s);
			s = p->left;
		}

	}
	void	deleteCase4(node_pointer& s, node_pointer& p)
	{
		if (s == p->right) {
			setColor(s, getColor(p));
			setColor(p, BLACK);
			setColor(s->right, BLACK);
			rotateLeft(p);
		}
		if (s == p->left) {
			setColor(s, getColor(p));
			setColor(p, BLACK);
			setColor(s->left, BLACK);
			rotateRight(p);
		}
	}
	void	fixAfterDelete(node_pointer node)
	{
		if (node == my_nullptr)
			return;
		if (node == getRoot()) {
			deleteRootCase(node);
			return;
		}
		if (getColor(node) == RED || getColor(node->left) == RED|| getColor(node->right) == RED) {
			deleteRedCase(node);
			return;
		}
		node_pointer s = my_nullptr;
		node_pointer p = my_nullptr;
		node_pointer tmp = node;
		setColor(tmp, DBLACK);
		while (tmp != getRoot() && getColor(tmp) == DBLACK) {
			p = tmp->parent;
			s = (tmp == p->left) ? p->right : p->left;
			if (getColor(s) == RED)
				deleteCase1(s, p);
			else if (getColor(s->left) == BLACK && getColor(s->right) == BLACK)
				deleteCase2(s, p, tmp);
			else {
				if ((tmp == p->left && getColor(s->right) == BLACK)
				|| (tmp == p->right && getColor(s->left) == BLACK))
					deleteCase3(s, p);
				deleteCase4(s, p);
				break;
			}
		}
		if (node == node->parent->left)
			node->parent->left = my_nullptr;
		else
			node->parent->right = my_nullptr;
		_node_alloc.destroy(node);
		_node_alloc.deallocate(node, 1);
		setColor(getRoot(), BLACK);
	}
	node_pointer	deleteNode(node_pointer node, const value_type& val) {
		if (node == my_nullptr)
			return node;
		if (_comp(node->value, val))
			return deleteNode(node->right, val);
		if (_comp(val, node->value))
			return deleteNode(node->left, val);
		if (node->left == my_nullptr || node->right == my_nullptr)
			return node;
		node_pointer tmp = minValueNode(node->right);
		if (tmp->parent == node) {
			if (node->parent && node->parent->left == node)
				node->parent->left = tmp;
			if (node->parent && node->parent->right == node)
				node->parent->right = tmp;
			tmp->left = node->left;
			node->left->parent = tmp;
			node->left = my_nullptr;
			tmp->parent = node->parent;
			node->parent = tmp;
			node->right = tmp->right;
			tmp->right = node;
			std::swap(tmp->color, node->color);
		} else {
			if (node->parent && node->parent->left == node)
				node->parent->left = tmp;
			if (node->parent && node->parent->right == node)
				node->parent->right = tmp;
			if (tmp->parent->left == tmp)
				tmp->parent->left = node;
			if (tmp->parent->right == tmp)
				tmp->parent->right = node;
			node_pointer tmp2 = tmp->parent;
			node->right->parent = tmp;
			tmp->parent = node->parent;
			node->parent = tmp2;
			tmp->left = node->left;
			node->left->parent = tmp;
			node->left = my_nullptr;
			tmp2 = tmp->right;
			tmp->right = node->right;
			node->right = tmp2;
			std::swap(tmp->color, node->color);
		}
		return deleteNode(tmp->right, val);
	}

};

}

#endif
