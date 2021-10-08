#ifndef RBTREE_UTILS_HPP
#define RBTREE_UTILS_HPP

#include "pair.hpp"
#include "colors.h"
#include "iterator.hpp"
#include "utils.hpp"
#include <iostream>

enum COLOR {
	RED,
	BLACK,
	FLUO
};

namespace ft
{
template <class T>
struct Node {
	struct Node<T>* left;
	struct Node<T>* right;
	struct Node<T>*	parent;
	enum COLOR		color;
	T				data;

	typedef T		value_type;
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

template< class T, class U >
bool operator<(const ft::Node<ft::pair<T, U> >& lhs, const ft::Node<ft::pair<T, U> >& rhs )
{
	return lhs.first < rhs.second;
};

} // namespace ft

#endif /* RBTREE_UTILS_HPP */
