#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "pair.hpp"

enum COLOR {
	RED,
	BLACK
};

namespace ft
{
template <class T>
struct node {
	struct node* 	left;
	struct node* 	right;
	struct node*	parent;
	COLOR			color;
	T*				data;
};

template <class T>
class rbtree
{
private:
	struct node<T>*	_root;
public:
	rbtree() {
		_root = nullptr;
	};
	~rbtree();
	
	void rotateRight(struct node *&root, struct node *&pt)
	{
		struct node *pt_left = pt->left;
	
		pt->left = pt_left->right;
	
		if (pt->left != NULL)
			pt->left->parent = pt;
	
		pt_left->parent = pt->parent;
	
		if (pt->parent == NULL)
			root = pt_left;
	
		else if (pt == pt->parent->left)
			pt->parent->left = pt_left;
	
		else
			pt->parent->right = pt_left;
	
		pt_left->right = pt;
		pt->parent = pt_left;
	}

	void rotateLeft(struct node *&root, struct node *&pt)
	{
		struct node *pt_right = pt->right;
	
		pt->right = pt_right->left;
	
		if (pt->right != NULL)
			pt->right->parent = pt;
	
		pt_right->parent = pt->parent;
	
		if (pt->parent == NULL)
			root = pt_right;
	
		else if (pt == pt->parent->left)
			pt->parent->left = pt_right;
	
		else
			pt->parent->right = pt_right;
	
		pt_right->left = pt;
		pt->parent = pt_right;
	}

	struct node *BSTInsert(struct node* root, struct node *pt)
	{
		if (root == NULL)
			return pt;
		if (pt->data < root->data)
		{
			root->left  = BSTInsert(_root->left, pt);
			root->left->parent = root;
		}
		else if (pt->data > root->data)
		{
			root->right = BSTInsert(root->right, pt);
			root->right->parent = root;
		}
		return  root;
	}

	void fixViolation(struct node *&root, struct node *&pt)
	{
		struct node *parent_pt = NULL;
		struct node *grand_parent_pt = NULL;
	
		while ((pt != root) && (pt->color != BLACK) &&
			(pt->parent->color == RED))
		{
	
			parent_pt = pt->parent;
			grand_parent_pt = pt->parent->parent;
	
			/*  Case : A
				Parent of pt is left child 
				of Grand-parent of pt */
			if (parent_pt == grand_parent_pt->left)
			{
	
				Node *uncle_pt = grand_parent_pt->right;
	
				/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
				if (uncle_pt != NULL && uncle_pt->color == 
													RED)
				{
					grand_parent_pt->color = RED;
					parent_pt->color = BLACK;
					uncle_pt->color = BLACK;
					pt = grand_parent_pt;
				}
	
				else
				{
					/* Case : 2
					pt is right child of its parent
					Left-rotation required */
					if (pt == parent_pt->right)
					{
						rotateLeft(root, parent_pt);
						pt = parent_pt;
						parent_pt = pt->parent;
					}
	
					/* Case : 3
					pt is left child of its parent
					Right-rotation required */
					rotateRight(root, grand_parent_pt);
					swap(parent_pt->color, 
							grand_parent_pt->color);
					pt = parent_pt;
				}
			}
	
			/* Case : B
			Parent of pt is right child 
			of Grand-parent of pt */
			else
			{
				Node *uncle_pt = grand_parent_pt->left;
	
				/*  Case : 1
					The uncle of pt is also red
					Only Recoloring required */
				if ((uncle_pt != NULL) && (uncle_pt->color == 
														RED))
				{
					grand_parent_pt->color = RED;
					parent_pt->color = BLACK;
					uncle_pt->color = BLACK;
					pt = grand_parent_pt;
				}
				else
				{
					/* Case : 2
					pt is left child of its parent
					Right-rotation required */
					if (pt == parent_pt->left)
					{
						rotateRight(root, parent_pt);
						pt = parent_pt;
						parent_pt = pt->parent;
					}
	
					/* Case : 3
					pt is right child of its parent
					Left-rotation required */
					rotateLeft(root, grand_parent_pt);
					swap(parent_pt->color, 
							grand_parent_pt->color);
					pt = parent_pt;
				}
			}
		}
	
		root->color = BLACK;
	}

	void start(T newdata)
	{
		struct node *node_pt = new_node(newdata);
			// Do a normal BST insert
		_root = BSTInsert(_root, node_pt);
		// fix Red Black Tree violations
		fixViolation(_root, node_pt);
	}
	
	struct node& new_node(T newdata) {
		struct node<T> newnode = new struct node<T>;
		newnode = {nullptr, nullptr, nullptr, RED, newdata};
		return newnode;
	}
};


} // namespace ft

#endif /* RBTREE_HPP */
