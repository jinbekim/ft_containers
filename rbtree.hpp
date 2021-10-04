#ifndef RBTREE_HPP
# define RBTREE_HPP

#include <iostream>
typedef struct node_
{
	int	color;
	int value;
	struct node_ *parent, *left, *right;

} Node;


class rbtree
{
	private:
		Node	*root;
	public:

		rbtree(/* args*/);
		rbtree(const rbtree &ref);
		~rbtree();
		rbtree& operator=(const rbtree &ref);


	void	rotateLeft(Node	*nod)
	{
		Node*	rightChild = nod->right;

		nod->right = rightChild->left;
		if (nod->right != nullptr)
			nod->right->parent = nod;
		rightChild->parent = nod->parent;
		if (nod->parent == nullptr)
			root = rightChild;
		else if (nod == nod->parent->left)
			nod->parent->left = rightChild;
		else if (nod == nod->parent->right)
			nod->parent->right = rightChild;
		rightChild->left = nod;
		nod->parent = rightChild;
	}
};

#endif
