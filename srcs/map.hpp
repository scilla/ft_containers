#ifndef MAP_HPP
#define MAP_HPP
#include "iterator.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <iterator>
#include <exception>
#include "utils.hpp"
#include "enable_if.hpp"
#include <stdio.h>
#include "rbtree.hpp"
#include "pair.hpp"
#include "colors.h"

namespace ft {

template< class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
public:
	typedef Key									key_type;
	typedef T									mapped_key;
	typedef typename ft::pair<Key, T>			value_type;
	typedef size_t								size_type;
	typedef std::ptrdiff_t						difference_type; // std:: cause linux
	typedef Compare								key_compare;
	typedef Allocator							allocator_type;
	typedef value_type&							reference;
	typedef const value_type&					const_reference;
	typedef typename Allocator::pointer			pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef Node<value_type>					node_type;
	
	class value_compare: public ft::binary_function<value_type, value_type, bool>
	{
	protected:
		key_compare comp;
	public:
		value_compare(): comp() {}
		value_compare(key_compare c): comp(c) {}
		bool operator()(value_type& lhs, value_type& rhs) {
			return comp(lhs.first, rhs.first);
		}
		bool operator()(const value_type& lhs, const value_type& rhs) const {
			return comp(lhs.first, rhs.first);
		}
	};

	typedef rbt_iterator<value_type, value_compare>			iterator;
	typedef const_rbt_iterator<value_type, value_compare> 		const_iterator;
	typedef const_reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef reverse_iterator<iterator>			reverse_iterator;


	// (con|de)structor
	explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _tree(NULL), _comp(comp), _alloc(alloc),  _size(0) {
		_tree = tree_alloc.allocate(1);
		tree_alloc.construct(_tree);
	}
	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _tree(NULL), _comp(comp), _alloc(alloc), _size(0) {
		_tree = tree_alloc.allocate(1);
		tree_alloc.construct(_tree);
		for (; first != last; first++) {
			insert(*first);
		}
	}

	map(map& new_map)
	: _tree(NULL), _comp(new_map._comp), _alloc(new_map._alloc), _size(new_map.size())
	{
		_tree = tree_alloc.allocate(1);
		tree_alloc.construct(_tree);
		*_tree = *new_map._tree;
	}

	~map() {
		clear();
		delete _tree;
	}

	void print(std::string s = "") {
		_tree->print_tree(s);
	}

	// cose
	map& operator=( map& other ) {
		clear();
		delete _tree;
		_tree = tree_alloc.allocate(1);
		tree_alloc.construct(_tree);
		*_tree = *other._tree;
		_comp = other._comp;
		_alloc = other._alloc;
		_size = other._size;
		return *this;
	}
	allocator_type get_allocator() const { return _alloc; }

	class outOfBoundException: public std::exception
	{
	public:
		virtual const char* what() const throw() {
			return "Out of Bound exception";
		}
	};
	
	// access
	T& at( const Key& key ) {
		node_type *res = _tree->find(key);
		if (res == end().base())
			throw outOfBoundException();
		return res->data->second;
	}

	const T& at( const Key& key ) const {
		node_type *res = _tree->find(key);
		if (res == end().base())
			throw outOfBoundException();
		return res->data->second;
	}

	T& operator[]( const Key& key ) {
		T* nt = new T();
		value_type pp = ft::make_pair(key, *nt);
		delete nt;
		node_type *res = _tree->find(pp);
		if (res == end().base()) {
			return insert(pp).first->second;
		}
		return res->data.second;
	};

	// iterators
	iterator begin() {
		if (!_tree->_root)
			return end();
		node_type* pt = _tree->_root;
		while (pt->left && pt->left->color != FLUO)
			pt = pt->left;
		return iterator(*pt);
	};

	const_iterator begin() const {
		if (!_tree->_root)
			return end();
		node_type* pt = _tree->_root;
		while (pt->left && pt->left->color != FLUO)
			pt = pt->left;
		return const_iterator(*pt);
	};


	iterator end() { return iterator(_tree->getEnd()); };
	const_iterator end() const { return const_iterator(_tree->getEnd()); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	// capacity
	bool empty() const { return !_size; }
	size_type size() const { return _size; }
	size_type max_size() const { return _tree->max_size(); }

	// modifiers
	void clear() {
		_size = 0;
		_tree->clear();
	}

	ft::pair<iterator, bool> insert(const value_type& value ) {
		node_type* nd = _tree->find(value);
		if (nd != end().base())
			return ft::make_pair(iterator(*nd), false);
		nd = &_tree->insert(value);
		_size++;
		// print();
		return ft::make_pair(iterator(*nd), true);
	}

	// any kind of optimization is useless with binary insertion
	// thus we'll just ignore hint
	iterator insert( iterator hint, const value_type& value ) {
		(void)hint;
		return insert(value).first;
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last, typename enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 ) {
		for (; first != last; first++)
			insert(*first);
	}

	void erase( iterator pos ) {
		_tree->deleteNode(pos.base());
		_size--;
	}

	size_type erase (const key_type& k) {
		iterator found = find(k);
		if (found != end()) {
			_tree->deleteNode(found.base());
			_size--;
			return 1;
		}
		return 0;
	}

	void erase (iterator first, iterator last) {
		iterator todel;
		while (first != last)
		{
			todel = first;
			++first;
			erase(todel);
		}
	}

	void swap( map& other ) {
		std::swap(_tree, other._tree);
		std::swap(_size, other._size);
	}

	// lookup
	size_type count( const Key& key ) const {
		size_type s = 0;
		for (const_iterator it = begin(); it != end(); it++)
			if ((*it).first == key)
				s++;
		return s;
	}
	iterator find( const Key& key ) {
		return iterator(*_tree->find(ft::make_pair(key, T())));
	}
	const_iterator find( const Key& key ) const {
		return const_iterator(*_tree->find(ft::make_pair(key, T())));
	}
	ft::pair<iterator,iterator> equal_range( const Key& key ) {
		return ft::make_pair(iterator(lower_bound(key)), iterator(upper_bound(key)));
	}
	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
		return ft::make_pair(const_iterator(lower_bound(key)), const_iterator(upper_bound(key)));
	}
	iterator lower_bound( const Key& key ) {
		node_type* n;
		node_type* res;
		res = end().base();
		if (!_size)
			return iterator(*res);
		n = _tree->_root;
		while (1)
		{
			if ((*n).data.first == key) {
				res = n;
				break;
			}
			else if ( !key_comp()((*n).data.first, key)) {
				res = n;
				if (!n->left || n->left->color == FLUO)
					break;
				n = n->left;
			} else if (key_comp()((*n).data.first, key)) {
				if (!n->right)
					break;
				n = n->right;
			}
		}
		return iterator(*res);
	}
	const_iterator lower_bound( const Key& key ) const {
		node_type* n;
		const node_type* res;
		res = end().base();
		if (!_size)
			return const_iterator(*res);
		n = _tree->_root;
		while (1)
		{
			if ((*n).data.first == key) {
				res = n;
				break;
			}
			else if ( !key_comp()((*n).data.first, key)) {
				res = n;
				if (!n->left || n->left->color == FLUO)
					break;
				n = n->left;
			} else if ( key_comp()((*n).data.first, key)) {
				if (!n->right)
					break;
				n = n->right;
			}
		}
		return const_iterator(*res);
	}
	iterator upper_bound( const Key& key ) {
		node_type* n;
		node_type* res;
		res = end().base();
		if (!_size)
			return iterator(*res);
		n = _tree->_root;
		while (1)
		{
			if ((*n).data.first == key) {
				if (!n->right || n->right->color == FLUO)
					break;
				n = n->right;
			}
			else if ( !key_comp()((*n).data.first, key)) {
				res = n;
				if (!n->left || n->left->color == FLUO)
					break;
				n = n->left;
			} else if ( key_comp()((*n).data.first, key)) {
				if (!n->right)
					break;
				n = n->right;
			}
		}
		return iterator(*res);
	}
	const_iterator upper_bound( const Key& key ) const {
		node_type* n;
		const node_type* res;
		res = end().base();
		if (!_size)
			return const_iterator(*res);
		n = _tree->_root;
		while (1)
		{
			if ((*n).data.first == key) {
				if (!n->right || n->right->color == FLUO)
					break;
				n = n->right;
			}
			else if ( !key_comp()((*n).data.first, key)) {
				res = n;
				if (!n->left || n->left->color == FLUO)
					break;
				n = n->left;
			} else if ( key_comp()((*n).data.first, key)) {
				if (!n->right)
					break;
				n = n->right;
			}
		}
		return const_iterator(*res);
	}

	// observer
	key_compare key_comp() const { return Compare(); }
	value_compare value_comp() const { return value_compare(); }
private:

	RBTree<value_type, value_compare>*					_tree;
	key_compare											_comp;
	allocator_type										_alloc;
	size_type											_size;
	std::allocator<RBTree<value_type, value_compare> >	tree_alloc;

};

template< class Key, class T, class Compare, class Alloc >
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
};

template< class Key, class T, class Compare, class Alloc >
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ){
	return (!(lhs == rhs));
};

template< class Key, class T, class Compare, class Alloc >
bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return(!(rhs < lhs));
};

template< class Key, class T, class Compare, class Alloc >
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return (rhs < lhs);
};
template< class Key, class T, class Compare, class Alloc >
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
{
	return(!(lhs < rhs));
}


}
#endif /* MAP_HPP */
