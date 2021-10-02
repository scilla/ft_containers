#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "pair.hpp"
#include "colors.h"
#include "iterator.hpp"
#include "utils.hpp"
#include "node.hpp"
#include <iostream>

enum COLOR {
	RED,
	BLACK,
	FLUO
};

namespace ft
{
template <class T>
class rbt_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef T							iterator_type;
	typedef T*							iterator_value;
	typedef T&							reference;
	typedef T*							pointer;
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
			// return *this;
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
			// throw outOfBoundException();
		}
		return *this;
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
			// return *this;
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
			// throw outOfBoundException();
		}
		return *this;
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
			// return *this;
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
			// throw outOfBoundException();
		}
		return *this;
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
			// return *this;
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
			// throw outOfBoundException();
		}
		return *this;
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

} // namespace ft

#endif /* RBTREE_ITERATOR_HPP */
