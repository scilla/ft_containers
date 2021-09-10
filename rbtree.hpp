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

	void insert(T& newdata) {
		
	}
	
	struct node& new_node(T newdata) {
		struct node<T> newnode = new struct node<T>;
		newnode = {nullptr, nullptr, nullptr, RED, newdata};
		return newnode;
	}
};
} // namespace ft

#endif /* RBTREE_HPP */
