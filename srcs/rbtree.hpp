#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "pair.hpp"
#include "colors.h"
#include "utils.hpp"
#include "rbtree_utils.hpp"
#include "rbtree_iterator.hpp"
#include <iostream>

namespace ft
{
template <class T, class Compare = ft::less<ft::Node<T> >, class Alloc = std::allocator<Node<T> > >
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

protected:
	allocator_type		_alloc;
	node				_start;
	node				_end;
	node*				_start_ptr;
	node*				_end_ptr;
	node**				_start_placed;
	node**				_end_placed;
	Compare				_comp;
	
public:
	node*	_root;

	size_type	max_size() const { return _alloc.max_size(); }

	RBTree(): _comp(), _root(NULL) { initialize_bounds(); }
	RBTree(RBTree& tree): _comp(), _root(NULL) {
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
			if (!_comp(data, start->data) && !_comp(start->data, data))
				return start;
			else if (_comp(data, start->data))
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
			if (!_comp(data, start->data) && !_comp(start->data, data))
				return start;
			else if (_comp(data, start->data))
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

	node* replaceNodeWithLoneChild(node* a, node* b) {
		if (b->parent != a)
			throw std::exception();
		if (a->left && a->right)
			throw std::exception();
		if (!a->left && !a->right)
			throw std::exception();
		b->parent = a->parent;
		*selfParentPtr(a) = b;
		return b;
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
			n = replaceNodeWithLoneChild(n, n->right);
			fixDeletion(n);
		} else if (!n->right) {
			n = replaceNodeWithLoneChild(n, n->left);
			fixDeletion(n);
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
			if (N->parent->color == BLACK && N->sibling() &&		// case 3
				N->sibling()->color == BLACK &&
				(!N->sibling()->left || N->sibling()->left->color == BLACK) &&	
				(!N->sibling()->right || N->sibling()->right->color == BLACK))
			{
				N->sibling()->color = RED;
				fixDeletion(N->parent);
			}
			else if (N->parent->color == RED &&	N->sibling() &&		// case 4
				N->sibling()->color == BLACK &&
				(!N->sibling()->left || N->sibling()->left->color == BLACK) &&	
				(!N->sibling()->right || N->sibling()->right->color == BLACK))
			{
				N->sibling()->color = RED;
				N->parent->color = BLACK;
			}
			else if (N->isLeft() &&	N->sibling() &&				// case 5
				N->sibling()->color == BLACK &&
				N->sibling()->left && N->sibling()->left->color == RED &&	
				(!N->sibling()->right || N->sibling()->right->color == BLACK))
			{
				N->sibling()->color = RED;
				N->sibling()->left->color = BLACK;
				rotateRight(N->sibling());
			}
			else if (N->isRight() && N->sibling() &&			// still case 5
				N->sibling()->color == BLACK &&
				N->sibling()->right && N->sibling()->right->color == RED &&	
				(!N->sibling()->left || N->sibling()->left->color == BLACK))
			{
				N->sibling()->color = RED;
				N->sibling()->right->color = BLACK;
				rotateLeft(N->sibling());
			}
			if (N->sibling())
				N->sibling()->color = N->parent->color; // case 6
			N->parent->color = BLACK;
			
			if (N->sibling()) {
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
			if (!_comp(N->data, parent->data) &&  !_comp(parent->data, N->data))
				throw duplicateElementException();
			else if (_comp(N->data, parent->data))
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

	void initialize_bounds() {
		_end = (node){NULL, NULL, NULL, FLUO, T()};
		_start = (node){NULL, NULL, NULL, FLUO, T()};
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
			std::cout << "(" << n->parent->data.first << ")";
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
