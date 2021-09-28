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
			throw outOfBoundException();
		}
	}

	rbt_iterator operator++(int) {
		rbt_iterator tmp = *this;
		++*this;
		return tmp;
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
			throw outOfBoundException();
		}
	}

	rbt_iterator operator--(int) {
		rbt_iterator tmp = *this;
		--*this;
		return tmp;
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

	struct ft::Node<T>* base() { return _ptr; }
	struct ft::Node<T>* base() const { return _ptr; }

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
	explicit const_rbt_iterator(struct Node<T>& newnode): _ptr(&newnode) {}
	explicit const_rbt_iterator(const struct Node<T>& newnode): _ptr((struct Node<T>*)&newnode) {}

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
				if (_ptr->color == FLUO || _ptr->parent->data > _ptr->data) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
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
				if (_ptr->color == FLUO || _ptr->parent->data < _ptr->data) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
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

template <class T, class Compare = std::less<T>, class Alloc = std::allocator<Node<T> > >
class RBTree
{
	typedef struct ft::Node<T>									node;
	typedef Alloc												allocator_type;
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::value_type					value_type;
	typedef typename allocator_type::const_pointer				const_pointer;
	typedef typename allocator_type::size_type					size_type;
	typedef typename allocator_type::difference_type			difference_type;

private:
	allocator_type		_alloc;
	node				_start;
	node				_end;
	node*				_start_ptr;
	node*				_end_ptr;
	node**				_start_placed;
	node**				_end_placed;
public:

	size_type	max_size() const { return _alloc.max_size(); }

	node*	_root;
	RBTree(): _root(NULL) { initialize_bounds(); }
	RBTree(RBTree& tree): _root(NULL) {
		initialize_bounds();
		*this = tree;
	}
	
	~RBTree() {
		clear();
	}

	void recursive_insert(node* new_node) {
		if (!new_node)
			return;
		if (new_node->color == FLUO)
			return;
		insert(new_node->data);
		recursive_insert(new_node->left);
		recursive_insert(new_node->right);
	}

	const node& getEnd() const { return _end; }
	const node& getStart() const { return _start; }

	RBTree& operator=(const RBTree& tree) {
		clear();
		recursive_insert(tree._root);
		return *this;
	}

	void clear() {
		remove_bounds();
		_nuke(_root);
		_root = NULL;
		add_bounds();
	}

	node& insert(T newdata) {
		node* ret = newNode(newdata);
		node* N = ret;
		remove_bounds();
		binaryInsert(N);
		fixTree(ret);
		while (_root->parent)
			_root = _root->parent;
		add_bounds();
		return *ret;
	}

	node* find(T& data) const {
		node* start = _root;
		while (start && start->color != FLUO)
		{
			if (data == start->data)
				return start;
			else if (data < start->data)
				start = start->left;
			else
				start = start->right;
		}
		return _end_ptr;
	}

	node* find(const T& data) const {
		node* start = _root;
		while (start && start->color != FLUO)
		{
			if (data == start->data)
				return start;
			else if (data < start->data)
				start = start->left;
			else
				start = start->right;
		}
		return _end_ptr;
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

	node** selfParentPtrCross(node* n, node* p) {
		if (!n->parent)
			return &_root;
		else if (n->parent->left == p)
			return &n->parent->left;
		else if (n->parent->right == p)
			return &n->parent->right;
		throw std::exception();
	}

	node** selfParentPtr(node* n) {
		if (!n->parent)
			return &_root;
		else if (n->isLeft())
			return &n->parent->left;
		else if (n->isRight())
			return &n->parent->right;
		throw std::exception();
	}

	node* minimumNode(node* n) {
		while (n->left)
			n = n->left;
		return n;
	}

	void fixDependencies(node* n) {
		if (n->left)
			n->left->parent = n;
		if (n->right)
			n->right->parent = n;
	}

	void swapNode(node* a, node* b) {
		*selfParentPtr(a) = b;
		*selfParentPtr(b) = a;
		std::swap(a->parent, b->parent);
		std::swap(a->left, b->left);
		std::swap(a->right, b->right);
		std::swap(a->color, b->color);
		fixDependencies(a);
		fixDependencies(b);
	}

	void replaceNodeWithLoneChild(node* a, node* b) {
		if (b->parent != a)
			throw std::exception();
		if (a->left && a->right)
			throw std::exception();
		if (!a->left && !a->right)
			throw std::exception();
		b->parent = a->parent;
		*selfParentPtr(a) = b;
	}

	void deleteNode(node* n) {
		remove_bounds();
		_deleteNode(n);
		delete n;
		add_bounds();
	}

	void _deleteNode(node* n) {
		node* x;
		if (!n->parent && !n->left && !n->right) {
			_root = NULL;
		} else if (!n->left && !n->right) {
			if (n->isLeft())
				n->parent->left = NULL;
			else if (n->isRight())
				n->parent->right = NULL;
			else
				throw std::exception();
		} else if (n->left && n->right) {
			x = minimumNode(n->right);
			swapNode(n, x);
			_deleteNode(n);
		} else if (!n->left) {
			replaceNodeWithLoneChild(n, n->right);
		} else if (!n->right) {
			replaceNodeWithLoneChild(n, n->left);
		} else
			throw std::exception();
	}

	void fixDeletion(node* N) {
		if (N->parent) {							// case 1
			if (N->sibling() && N->sibling()->color == RED) 		// case 2
			{
				N->parent->color = RED;
				N->sibling()->color = BLACK;
				if (N->isLeft())
					rotateLeft(N->parent);
				else
					rotateRight(N->parent);
			}
			if (N->parent->color == BLACK &&		// case 3
				(!N->sibling() || N->sibling()->color == BLACK) &&
				(!N->sibling()->left || N->sibling()->left->color == BLACK) &&	
				(!N->sibling()->right || N->sibling()->right->color == BLACK))
			{
				N->sibling()->color = RED;
				fixDeletion(N->parent);
			}
			else if (N->parent->color == RED &&		// case 4
				(!N->sibling() || N->sibling()->color == BLACK) &&
				(!N->sibling()->left || N->sibling()->left->color == BLACK) &&	
				(!N->sibling()->right || N->sibling()->right->color == BLACK))
			{
				N->sibling()->color = RED;
				N->parent->color = BLACK;
			}
			else if (N->isLeft() &&					// case 5
				(!N->sibling() || N->sibling()->color == BLACK) &&
				N->sibling()->left && N->sibling()->left->color == RED &&	
				(!N->sibling()->right || N->sibling()->right->color == BLACK))
			{
				N->sibling()->color = RED;
				N->sibling()->left->color = BLACK;
				rotateRight(N->sibling());
			}
			else if (N->isRight() &&				// still case 5
				(!N->sibling() || N->sibling()->color == BLACK) &&
				N->sibling()->right && N->sibling()->right->color == RED &&	
				(!N->sibling()->left || N->sibling()->left->color == BLACK))
			{
				N->sibling()->color = RED;
				N->sibling()->right->color = BLACK;
				rotateLeft(N->sibling());
			}
			N->sibling()->color = N->parent->color; // case 6
			N->parent->color = BLACK;
			if (N->isLeft()) {
				if (N->sibling()->right)
					N->sibling()->right->color = BLACK;
				rotateLeft(N->parent);
			} else {
				if (N->sibling()->right)
					N->sibling()->left->color = BLACK;
				rotateRight(N->parent);
			}
		}
	}

	class duplicateElementException: public std::exception
	{
	public:
		virtual const char* what() const throw() {
			return "Duplicate element exception";
		}
	};

	void binaryInsert(node* N) {
		node** current = &_root;
		node* parent = NULL;
		while (*current)
		{
			parent = *current;
			if (N->data < parent->data)
				current = &parent->left;
			else if (N->data > parent->data)
				current = &parent->right;
			else
				throw duplicateElementException();
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

	void initialize_bounds() {
		_end = (node){NULL, NULL, NULL, FLUO, ft::make_pair(0, "END*")};
		_start = (node){NULL, NULL, NULL, FLUO, ft::make_pair(0, "*START")};
		_end_ptr = &_end;
		_start_ptr = &_start;
		_end_placed = NULL;
		_start_placed = NULL;
	}
	
	void add_bounds() {
		node* ptr;
		if (!_root) {
			_start.parent = NULL;
			_end.parent = NULL;
			_start_placed = NULL;
			_end_placed = NULL;	
			return;
		}
		
		ptr = _root;
		while (ptr->left)
			ptr = ptr->left;
		ptr->left = &_start;
		_start.parent = ptr;
		_start_placed = &ptr->left;

		ptr = _root;
		while (ptr->right)
			ptr = ptr->right;
		ptr->right = &_end;
		_end.parent = ptr;
		_end_placed = &ptr->right;		
	}

	void remove_bounds() {
		_start.parent = NULL;
		_end.parent = NULL;
		if (_start_placed)
			*_start_placed = NULL;
		if (_end_placed)
			*_end_placed = NULL;
	}

	void print_tree(std::string s = "") {
		(void)s;
		//return;
		std::cout << BLUE << "<< " << s << " ####################" << std::endl;
		_print_tree(_root);
		std::cout << BLUE << s << " >> ####################" << std::endl;
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
		std::cout << coll << std::string(l * 4,' ');
		if (n->parent) {
			//std::cout << "(" << n->parent->data.first << ")";
			if (n->isLeft())
				std::cout << "\\";
			else
				std::cout << "/";
		}
		std::cout << n->data.first << NORMAL;
		_print_tree(n->left, l + 1);
	}
};


} // namespace ft

#endif /* RBTREE_HPP */
