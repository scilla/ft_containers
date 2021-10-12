#ifndef RBTREE_ITERATOR_HPP
#define RBTREE_ITERATOR_HPP

#include "pair.hpp"
#include "colors.h"
#include "iterator.hpp"
#include "utils.hpp"
#include "rbtree_utils.hpp"
#include <iostream>

namespace ft
{
template <class T, class Compare = ft::less<T>, bool enableConstConstructor = false >
class rbt_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef T							iterator_type;
	typedef T*							iterator_value;
	typedef T&							reference;
	typedef const T&							const_reference;
	typedef T*							pointer;

	explicit rbt_iterator(): _ptr(NULL) {}
	explicit rbt_iterator(struct Node<T>& newnode): _ptr(&newnode) {}
	explicit rbt_iterator(const struct Node<T>& newnode): _ptr((struct Node<T>*)&newnode) {}

	rbt_iterator(const rbt_iterator& newit): _ptr(NULL) { *this = newit; } 

	~rbt_iterator() {}
	reference operator*() { return _ptr->data; }
	pointer operator->() { return &_ptr->data; }
	const_reference operator*() const { return _ptr->data; }
	const pointer operator->() const { return &_ptr->data; }

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
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || (!_comp(_ptr->parent->data, _ptr->data) && _ptr->parent->data != _ptr->data)) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
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
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || _comp(_ptr->parent->data, _ptr->data)) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
		}
		return *this;
	}

	rbt_iterator operator--(int) {
		rbt_iterator tmp = *this;
		--*this;
		return tmp;
	}

	template <class K>
	rbt_iterator& operator=(const K& other) {
		_ptr = const_cast<struct Node<T>*>(other.base());
		return *this;
	}

	struct ft::Node<T>* base() { return _ptr; }
	const struct ft::Node<T>* base() const { return _ptr; }

	bool operator==(const rbt_iterator &other) { return _ptr == other.base(); }
	bool operator!=(const rbt_iterator &other) { return _ptr != other.base(); }
private:
	struct Node<T>*	_ptr;
	Compare		_comp;
};


template <class T, class Compare = ft::less<T>, bool enableConstConstructor = false >
class set_rbt_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef T							iterator_type;
	typedef T*							iterator_value;
	typedef T&							reference;
	typedef const T&							const_reference;
	typedef T*							pointer;
	typedef const T*							const_pointer;

	explicit set_rbt_iterator(): _ptr(NULL) {}
	explicit set_rbt_iterator(struct Node<T>& newnode): _ptr(&newnode) {}
	explicit set_rbt_iterator(const struct Node<T>& newnode): _ptr((struct Node<T>*)&newnode) {}

	set_rbt_iterator(const set_rbt_iterator& newit): _ptr(NULL) { *this = newit; } 

	template<class Iter>
	set_rbt_iterator(const Iter& newit)
	: _ptr(NULL)
	{ 
		*this = newit;
	} 

	~set_rbt_iterator() {}
	const_reference operator*() const { return _ptr->data; }
	const_pointer operator->() const { return &_ptr->data; }

	class outOfBoundException: public std::exception
	{
	public:
		virtual const char* what() const throw() {
			return "Out of Bound exception";
		}
	};

	set_rbt_iterator& operator++() {
		if(_ptr->right)
		{
			_ptr = _ptr->right;
			while(_ptr->left)
				_ptr = _ptr->left;
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || (!_comp(_ptr->parent->data, _ptr->data) && _ptr->parent->data != _ptr->data)) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
		}
		return *this;

	}

	set_rbt_iterator operator++(int) {
		set_rbt_iterator tmp = *this;
		++*this;
		return tmp;
	}
	
	set_rbt_iterator& operator--() {
		if(_ptr->left)
		{
			_ptr = _ptr->left;
			while(_ptr->right)
				_ptr = _ptr->right;
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || _comp(_ptr->parent->data, _ptr->data)) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
		}
		return *this;
	}

	set_rbt_iterator operator--(int) {
		set_rbt_iterator tmp = *this;
		--*this;
		return tmp;
	}
	template <class K>
	set_rbt_iterator& operator=(const K& other) {
		_ptr = const_cast<struct Node<T>*>(other.base());
		return *this;
	}

	struct ft::Node<T>* base() { return _ptr; }
	const struct ft::Node<T>* base() const { return _ptr; }

	bool operator==(const set_rbt_iterator &other) { return _ptr == other.base(); }
	bool operator!=(const set_rbt_iterator &other) { return _ptr != other.base(); }
private:
	struct Node<T>*	_ptr;
	Compare		_comp;
};

template <class T, class Compare = ft::less<T> >
class const_rbt_iterator: public ft::iterator<ft::bidirectional_iterator_tag, T>
{
public:
	typedef T												iterator_type;
	typedef T*												iterator_value;
	typedef T&												reference;
	typedef const T&										const_reference;
	typedef T*												pointer;
	typedef const T*										const_pointer;

	explicit const_rbt_iterator(): _ptr(NULL) {}
	explicit const_rbt_iterator(struct Node<T>& newnode): _ptr(&newnode) {}
	explicit const_rbt_iterator(const struct Node<T>& newnode): _ptr((struct Node<T>*)&newnode) {}
	template<class U, class V >
	const_rbt_iterator(const const_rbt_iterator<U, V>& newit) { *this = newit; } 
	template<class U, class V >
	const_rbt_iterator(const rbt_iterator<U, V>& newit) { *this = newit; } 

	~const_rbt_iterator() {}
	const_reference operator*() const { return _ptr->data; }
	const_pointer operator->() const { return &_ptr->data; }
	const_reference operator*() { return _ptr->data; }
	const_pointer operator->() { return &_ptr->data; }

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
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || (!_comp(_ptr->parent->data, _ptr->data) && _comp(_ptr->data, _ptr->parent->data))) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
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
		}
		else
		{
			while(_ptr->parent)
			{
				if (_ptr->color == FLUO || _comp(_ptr->parent->data, _ptr->data)) {
					_ptr = _ptr->parent;
					return (*this);
				}
				_ptr = _ptr->parent;
			}
		}
		return *this;
	}
	const_rbt_iterator operator--(int) {
		const_rbt_iterator tmp = *this;
		--*this;
		return tmp;
	}

	template <class K>
	const_rbt_iterator&	operator=(const K& other) {
		_ptr = other.base();
		return *this;
	}

	const struct Node<T>* base() { return _ptr; }
	const struct Node<T>* base() const { return _ptr; }

	bool operator==(const const_rbt_iterator &other) { return (_ptr->color == FLUO && other._ptr->color == FLUO) || _ptr == other.base(); }
	bool operator!=(const const_rbt_iterator &other) { return !(_ptr->color == FLUO && other._ptr->color == FLUO) && _ptr != other.base(); }
private:
	const struct Node<T>*	_ptr;
	Compare				_comp;
};

} // namespace ft

#endif /* RBTREE_ITERATOR_HPP */
