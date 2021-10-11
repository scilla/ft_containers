#ifndef NODE_HPP
#define NODE_HPP
#include "utils.hpp"

namespace ft {
	
template <class T>
struct Node {
	struct Node<T>* left;
	struct Node<T>* right;
	struct Node<T>*	parent;
	enum COLOR		color;
	T				data;

	typedef T		value_type;
	Node(T data): data(data), color(BLACK), parent(NULL), left(NULL), right(NULL) {};
	bool isLeft() { return (parent && parent->left == this); }
	bool isRight() { return (parent && parent->right == this); }
	struct Node<T>* sibling() {
		if (isLeft())
			return parent->right;
		return parent->left;
	}
	struct Node<T>* uncle() {
		if (parent)
			return parent->sibling();
		return NULL;
	}
	struct Node<T>* grandparent() {
		if (parent)
			return parent->parent;
		return NULL;
	}
};
} // namespace ft

#endif /* NODE_HPP */
