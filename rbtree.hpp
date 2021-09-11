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

	void insert(T& newdata) {
		node* N = newNode(newdata);
		binaryInsert(N);
		do {
			if (N->parent->color == RED)
				return;
			if (!N->parent)
				N->parent->color = BLACK; // case 4
			else {
				if (!N->uncle() || N->uncle()->color == BLACK)
					caseI56();
				else {
					N->parent->color = BLACK;
					N->uncle()->color = BLACK;
					N->parent->parent = RED;
					N = N->parent->parent;
				}
			}
		} while (N->parent);
	}

	void caseI56(node* N) {
		if (N == )
	}

	void binaryInsert(node* N) {
		node* current = _root;
		while (current)
		{
			if (N->data < current->data)
				current = current->left;
			else
				current = current->right;
		}
		current = N;
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
