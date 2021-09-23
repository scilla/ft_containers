#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "pair.hpp"
#include "colors.h"
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

template <class T>
class rbt_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef T												iterator_type;
	typedef T*												iterator_value;
	typedef T&												reference;
	typedef T*												pointer;
	//typedef bidirectional_iterator_tag						iterator_category;

	explicit rbt_iterator(): _ptr(NULL) {}
	explicit rbt_iterator(struct Node<T>& newnode): _ptr(&newnode) {}
	explicit rbt_iterator(const struct Node<T>& newnode): _ptr((struct Node<T>*)&newnode) {}

	rbt_iterator(const rbt_iterator& newit) { *this = newit; } 
	// rbt_iterator(const const_rbt_iterator<T>& newit) { *this = newit; } 
	// rbt_iterator(const ft::iterator<ft::bidirectional_iterator_tag, T>& newit) { *this = newit; } 
	//template<class U>
	// template<class U>
	// rbt_iterator(const const_rbt_iterator<U>& newit) { *this = newit; } 

	// template<class Iter>
	// rbt_iterator(const Iter& newit): _ptr(NULL) { *this = newit; } 

	~rbt_iterator() {}
	reference operator*() const { return _ptr->data; }
	pointer operator->() const { return &_ptr->data; }

	class outOfBoundException: public std::exception
	{
	public:
		virtual const char* what() const throw() {
			return "Out of Bound exception";
		}
	};

	rbt_iterator& operator++() {
		if(_ptr->right)
		{
			_ptr = _ptr->right;
			while(_ptr->left)
				_ptr = _ptr->left;
			return *this;
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || _ptr->parent->data > _ptr->data) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
			//exception
			// return(NULL);
			throw outOfBoundException();
		}
	}
	rbt_iterator operator++(int) {
		rbt_iterator tmp = *this;
		++*this;
		return *this;
	}
	rbt_iterator& operator--() {
		if(_ptr->left)
		{
			_ptr = _ptr->left;
			while(_ptr->right)
				_ptr = _ptr->right;
			return *this;
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || _ptr->parent->data < _ptr->data) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
			//exception
			//return(NULL);
			throw outOfBoundException();
		}
	}
	rbt_iterator operator--(int) {
		rbt_iterator tmp = *this;
		--*this;
		return *this;
	}

	// template <class K>
	// rbt_iterator&	operator=(const rbt_iterator<K> & other) {
	// 	_ptr = other.base();
	// 	return *this;
	// }

	template <class K>
	rbt_iterator& operator=(const K& other) {
		_ptr = other.base();
		return *this;
	}

	// pointer		base() const { return _ptr; }

	const struct Node<T>* base() { return _ptr; }
	const struct Node<T>* base() const { return _ptr; }

	bool operator==(const rbt_iterator &other) { return _ptr == other.base(); }
	bool operator!=(const rbt_iterator &other) { return _ptr != other.base(); }
private:
	struct Node<T>*		_ptr;
};

template <class T>
class const_rbt_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef T												iterator_type;
	typedef T*												iterator_value;
	typedef T&												reference;
	typedef const T&										const_reference;
	typedef T*												pointer;
	typedef const T*										const_pointer;
	//typedef bidirectional_iterator_tag						iterator_category;

	explicit const_rbt_iterator(): _ptr(NULL) {}
	explicit const_rbt_iterator(struct Node<T>& ptr): _ptr(&ptr) {}
	explicit const_rbt_iterator(const struct Node<T>& ptr): _ptr(&ptr) {}

	const_rbt_iterator(const const_rbt_iterator& newit) { *this = newit; } 
	const_rbt_iterator(const rbt_iterator<T>& newit) { *this = newit; } 
	// const_rbt_iterator(const ft::iterator<ft::bidirectional_iterator_tag, T>& newit) { *this = newit; } 
	// template<class U>
	// const_rbt_iterator(const const_rbt_iterator<U>& newit) { *this = newit; } 
	// template<class U>
	// const_rbt_iterator(const rbt_iterator<U>& newit) { *this = newit; } 

	// template<class Iter>
	// const_rbt_iterator(const Iter& newit): _ptr(NULL) { *this = newit; } 

	~const_rbt_iterator() {}
	const_reference operator*() const { return _ptr->data; }
	const_pointer operator->() const { return &_ptr->data; }

	class outOfBoundException: public std::exception
	{
	public:
		virtual const char* what() const throw() {
			return "Out of Bound exception";
		}
	};

	const_rbt_iterator& operator++() {
		if(_ptr->right)
		{
			_ptr = _ptr->right;
			while(_ptr->left)
				_ptr = _ptr->left;
			return *this;
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO)
					return (*this);
				if(_ptr->parent->data > _ptr->data) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
			//exception
			// return(NULL);
			throw outOfBoundException();
		}
	}
	const_rbt_iterator operator++(int) {
		const_rbt_iterator tmp = *this;
		++*this;
		return tmp;
	}
	const_rbt_iterator& operator--() {
		if(_ptr->left)
		{
			_ptr = _ptr->left;
			while(_ptr->right)
				_ptr = _ptr->right;
			return *this;
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO)
					return (*this);
				if(_ptr->parent->data < _ptr->data) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
			//exception
			//return(NULL);
			throw outOfBoundException();
		}
	}
	const_rbt_iterator operator--(int) {
		const_rbt_iterator tmp = *this;
		--*this;
		return tmp;
	}

	// template <class K>
	// const_rbt_iterator&	operator=(const const_rbt_iterator<K> & other) {
	// 	_ptr = other.base();
	// 	return *this;
	// }

	template <class K>
	const_rbt_iterator&	operator=(const K& other) {
		_ptr = other.base();
		return *this;
	}

	// pointer		base() const { return _ptr; }

	const struct Node<T>* base() { return _ptr; }
	const struct Node<T>* base() const { return _ptr; }

	bool operator==(const const_rbt_iterator &other) { return _ptr == other.base(); }
	bool operator!=(const const_rbt_iterator &other) { return _ptr != other.base(); }
private:
	const struct Node<T>*		_ptr;
};

template <class T, class Compare = std::less<T> >
class RBTree
{
	typedef struct Node<T>	node;
private:
public:
	node*	_root;
	RBTree(): _root(NULL) {}
	RBTree(RBTree& tree) {
		*this = tree;
	}
	~RBTree() {_nuke(_root);}
	void recursive_insert(node* new_node) {
		if (!new_node)
			return;
		insert(new_node->data);
		recursive_insert(new_node->left);
		recursive_insert(new_node->right);
	}

	RBTree& operator=(const RBTree& tree) {
		_nuke(_root);
		recursive_insert(tree._root);
		return *this;
	}

	node& insert(T newdata) {
		node* ret = newNode(newdata);
		node* N = ret;
		binaryInsert(N);
		fixTree(ret);
		while (_root->parent)
			_root = _root->parent;
		return *ret;
	}

	node* find(T& data) const {
		node* start = _root;
		while (start)
		{
			if (data == start->data)
				return start;
			else if (data < start->data)
				start = start->left;
			else
				start = start->right;
		}
		return NULL;
	}

	node* find(const T& data) const {
		node* start = _root;
		while (start)
		{
			if (data == start->data)
				return start;
			else if (data < start->data)
				start = start->left;
			else
				start = start->right;
		}
		return NULL;
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
				if (N->isRight() && N->parent->isLeft()) {
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
/*
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
		node* child = !N->right ? N->left : N->right;
		replaceNode(N, child);
		if (N->color == BLACK) {
			if (N->color == RED)
				child->color = BLACK;
			else
				fixDeletion(N);
		}
		delete N;
	}
*/
	void rbTransplant(node* u, node* v) {
		if (u->parent == NULL) {
			_root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	node* minimumNode(node *n) {
		while (n->left)
			n = n->left;
		return n;
	}
	node* maximumNode(node *n) {
		while (n->right)
			n = n->right;
		return n;
	}

	void deleteNode(node* n) {
		node* z = n;
		node *x, *y;
		// while (n != NULL) {
		// 	if (n->data == key) {
		// 		z = n;
		// 	}

		// 	if (n->data <= key) {
		// 		n = n->right;
		// 	} else {
		// 		n = n->left;
		// 	}
		// }
		// if (z == NULL) {
		// 	std::cout << "Key not found in the tree" << std::endl;
		// 	return;
		// }
		y = z;
		int y_original_color = y->color;
		if (z->left == NULL) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == NULL) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimumNode(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0) {
			// deleteFix(x);
			fixDeletion(x);
		}
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

	void binaryInsert(node* N) {
		node** current = &_root;
		node* parent = NULL;
		while (*current)
		{
			parent = *current;
			if (N->data < parent->data)
				current = &parent->left;
			else
				current = &parent->right;
		}
		*current = N;
		N->parent = parent;
	}

	node* newNode(T& newdata) {
		node* newNode = new node;
		newNode->color = RED;
		newNode->data = newdata;
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->parent = NULL;
		return newNode;
	}

	void rotateLeft(node* x) {
		node* y = x->right;
		x->right = y->left;
		if (y->left != NULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			_root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rotateRight(node* x) {
		node* y = x->left;
		x->left = y->right;
		if (y->right != NULL) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == NULL) {
			_root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void _nuke(node* n) {
		if (!n || n->color == FLUO)
			return;
		_nuke(n->left);
		_nuke(n->right);
		delete n;
	}


	void print_tree(std::string s = "") {
		std::cout << BLUE << s << "#####################################################" << std::endl;
		_print_tree(_root);
		std::cout << BLUE << s << "#####################################################" << std::endl;
	}
	void _print_tree(node* n, size_t l = 0) {
		if (!n) {
			std::cout << std::endl;
			return;
		}
		_print_tree(n->right, l + 1);
		std::string coll;
		switch (n->color)
		{
		case 0:
			coll = BOLD_RED;
			break;
		case 1:
			coll = BOLD_GREEN;
			break;
		case 2:
			coll = YELLOW;
			break;
		default:
			coll = BLUE;
			break;
		}
		std::cout << std::string(l * 5,' ') << coll << n->data.first;
		_print_tree(n->left, l + 1);
	}
};


} // namespace ft

#endif /* RBTREE_HPP */
