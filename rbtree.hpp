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
struct Node {
	struct Node* 	left;
	struct Node* 	right;
	struct Node*	parent;
	enum COLOR		color;
	T				data;

	bool isLeft() { return (parent && parent->left == this); }
	bool isRight() { return (parent && parent->right == this); }
	struct Node* sibling() {
		if (isLeft())
			return parent->right;
		return parent->left;
	}
	struct Node* uncle() {
		if (parent)
			return parent->sibling();
		return NULL;
	}
	struct Node* grandparent() {
		if (parent)
			return parent->parent;
		return NULL;
	}
};

template <class T>
class rbtree
{
	typedef struct Node<T>	node;
private:
	node*	_root;
public:
	rbtree() {
		_root = NULL;
	};
	~rbtree();

	node& insert(T& newdata) {
		node* ret = newNode(newdata);
		node* N = ret;
		binaryInsert(N);
		fixTree(N);
		return *ret;
	}

	void fixTree(node* N) {
		if (!N->parent)												// case 1
			N->color = BLACK;
		else if (N->parent->color == RED) 							// case 2
		{
			if (N->uncle() && N->uncle()->color == RED) {
				N->parent->color = BLACK;
				N->uncle()->color = BLACK;
				N->grandparent()->color = RED;
				fixTree(N->grandparent());
			}
			else { 													// case 4
				if (N->isRight() && N->parent()->isLeft()) {
					rotateLeft(N->parent);
					N = N->left;
				} else if (N->isLeft() && N->parent->isRight()) {
					rotateRight(N->parent);
					N = N->right;
				}
				N->parent->color = BLACK; 							// case 5
				N->grandparent()->color = RED;
				if (N->isLeft() && N->parent->isLeft()) {
					rotateRight(N->grandparent());
				} else {
					rotateLeft(N->grandparent());
				}
			}
		} 															// case 3
	}

	void replaceNode(node* a, node* b) {
		if (a->parent) {
			if (a->isLeft()) {
				a->parent->left = b;
			} else {
				a->parent->right = b;
			}
			b->parent = a->parent;
		}
	}

	void deleteNode(node* N) {
		node* child = !N->isRight() ? N->left : N->right;
		replaceNode(N, child);
		if (N->color == BLACK) {
			if (N->color == RED)
				child->color = BLACK;
			else
				fixDeletion(N);
		}
		delete N;
	}

	void fixDeletion(node* N) {
		if (N->parent) {							// case 1
			if (N->sibling()->color == RED) 		// case 2
			{
				N->parent->color = RED;
				N->sibling()->color = BLACK;
				if (N->isLeft())
					rotateLeft(N->parent);
				else
					rotateRight(N->parent);
			}
			if (N->parent->color == BLACK &&		// case 3
				N->sibling()->color == BLACK &&
				N->sibling()->left->color == BLACK &&	
				N->sibling()->right->color == BLACK)
			{
				N->sibling()->color = RED;
				fixDeletion(N->parent);
			}
			else if (N->parent->color == RED &&		// case 4
				N->sibling()->color == BLACK &&
				N->sibling()->left->color == BLACK &&	
				N->sibling()->right->color == BLACK)
			{
				N->sibling()->color = RED;
				N->parent->color = BLACK;
			}
			else if (N->isLeft() &&					// case 5
				N->sibling()->color == BLACK &&
				N->sibling()->left->color == RED &&	
				N->sibling()->right->color == BLACK)
			{
				N->sibling()->color = RED;
				N->sibling()->left->color = BLACK;
				rotateRight(N->sibling());
			}
			else if (N->isRight() &&				// still case 5
				N->sibling()->color == BLACK &&
				N->sibling()->right->color == RED &&	
				N->sibling()->left->color == BLACK)
			{
				N->sibling()->color = RED;
				N->sibling()->right->color = BLACK;
				rotateLeft(N->sibling());
			}
			N->sibling()->color = N->parent->color; // case 6
			N->parent->color = BLACK;
			if (N->isLeft()) {
				N->sibling()->right->color = BLACK;
				rotateLeft(N->parent);
			} else {
				N->sibling()->left->color = BLACK;
				rotateRight(N->parent);
			}
		}
	}

	void binaryInsert(node* N) {  // fortissimi dubbi
		node** current = &_root;
		node* parent = _root->parent;
		while (*current)
		{
			parent = *current;
			if (N->data < parent->data)
				*current = parent->left;
			else
				*current = parent->right;
		}
		*current = N;
		N->parent = parent;
	}

	node* newNode(T& newdata) {
		node* newNode = new node;
		newNode->color = RED;
		newNode->data = &newdata;
		return newNode;
	}

	node* rotateDirRoot(node* P, bool right) {
		node* G = this->parent;
		node* S = right ? this->left : this->right;
		node* C;
		if (!S)
			return this;
		C = right ? this->right: this->left;
		this->left = right ? C : this;
		S->right = right ? this : C;
		if (C)
			C->parent = this;
		this->parent = S;
		S->parent = G;
		if (G)
		{
			if (P == G->right)
				G->right = S;
			else
				G->left = S;
		}
		else
			_root = S;
		return S;
	}

	node* rotateLeft(node* P) { return rotateDirRoot(P, false); }
	node* rotateRight(node* P) { return rotateDirRoot(P, true); }
};
} // namespace ft

#endif /* RBTREE_HPP */
