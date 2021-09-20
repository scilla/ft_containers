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

namespace ft {

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
class map {
public:
	typedef Key									key_type;
	typedef T									mapped_key;
	typedef typename ft::pair<const Key, T>		value_type;
	typedef size_t								size_type;
	typedef ptrdiff_t							difference_type;
	typedef Compare								key_compare;
	typedef Allocator							allocator_type;
	typedef value_type&							reference;
	typedef const value_type&					const_reference;
	typedef typename Allocator::pointer			pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef rbt_iterator<value_type>			iterator;
	typedef const rbt_iterator<const value_type> const_iterator;
	typedef reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef reverse_iterator<iterator>			reverse_iterator;
	typedef Node<T>								node_type;
	
	class value_compare: public std::binary_function<value_type, value_type, bool>
	{
		friend class map;
	protected:
		key_compare comp;
		value_compare(key_compare c): comp(c) {}
	public:
		bool operator()(const value_type& lhs, const value_type& rhs) const {
			return comp(lhs.first, rhs.first);
		}
	};

	// (con|de)structor
	explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _alloc(alloc), _comp(comp) {}
	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _alloc(alloc), _comp(comp) {
		for (; first != last; first++) {
			_tree.insert(*first);
			_size++;
		}
		add_bounds();
	}

	map(map& new_map) {
		*this = new_map;
		add_bounds();
	}

	~map() {}

	// cose
	map& operator=( const map& other ) {
		remove_bounds();
		_tree = other._tree;
		_comp = other._comp;
		_alloc = other._alloc;
		_size = other._size;
		add_bounds();
		return *this;
	}
	allocator_type get_allocator() const { return _alloc; }

	class outOfBoundException: public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
	
	// access
	T& at( const Key& key ) {
		node_type *res = _tree.find(key);
		if (!res)
			throw outOfBoundException();
		return res->data->second;
	}

	const T& at( const Key& key ) const {
		node_type *res = _tree.find(key);
		if (!res)
			throw outOfBoundException();
		return res->data->second;
	}

	T& operator[]( const Key& key ) {
		node_type *res = _tree.find(key);
		if (!res)
			return insert(std::make_pair(key, T())).first->second;
		return res->data->second;
	};

	// iterators

	iterator begin() {  //da controllare
		node_type* pt = _tree._root;
		if(!_tree._root)
			return end();
		while (pt->color != FLUO)
			pt--;
		return iterator(pt);
	};

	const_iterator begin() const {
		node_type* pt = _tree._root;
		if(!_tree._root)
			return end();
		while (pt->color != FLUO)
			pt--;
		return const_iterator(pt);
	};

	iterator end() { return iterator(_end);	};
	const_iterator end() const { return const_iterator(_end); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	// capacity
	bool empty() const { return !_size; }
	size_type size() const { return _size; } ;
	size_type max_size() const { return _alloc.max_size(); } 

	// modifiers
	void clear() {
		remove_bounds();
		_size = 0;
		_tree._nuke(_tree._root);
	}
	std::pair<iterator, bool> insert( const value_type& value );
	iterator insert( iterator hint, const value_type& value );
	template< class InputIt >
	void insert( InputIt first, InputIt last );
	void erase( iterator pos );
	void swap( map& other );

	// lookup
	size_type count( const Key& key ) const;
	iterator find( const Key& key );
	const_iterator find( const Key& key ) const;
	std::pair<iterator,iterator> equal_range( const Key& key );
	std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
	iterator lower_bound( const Key& key );
	const_iterator lower_bound( const Key& key ) const;
	iterator upper_bound( const Key& key );
	const_iterator upper_bound( const Key& key ) const;

	// observer
	key_compare key_comp() const;
	map::value_compare value_comp() const;
private:
	void add_bounds() {
		node_type* ptr;
		if (!_tree._root)
			return;
		ptr = _tree._root;
		while (ptr->left)
			ptr = ptr->left;
		ptr->left = &_start;
		_start.parent = ptr;
		_start_ptr = &ptr->left;		
		ptr = _tree._root;
		while (ptr->right)
			ptr = ptr->right;
		ptr->right = &_end;
		_end.parent = ptr;
		_end_ptr = &ptr->right;		
	}

	void remove_bounds() {
		if (!_tree._root)
			return;
		*_start_ptr = NULL;
		*_end_ptr = NULL;
		_start.parent = NULL;
		_end.parent = NULL;
	}

	RBTree<value_type>		_tree;
	node_type				_start;
	node_type				_end;
	node_type**				_start_ptr;
	node_type**				_end_ptr;
	key_compare				_comp;
	allocator_type			_alloc;
	size_type				_size;
};

template< class Key, class T, class Compare, class Alloc >
bool operator==(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator!=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator<(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator<=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator>(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );
template< class Key, class T, class Compare, class Alloc >
bool operator>=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

}

#endif /* MAP_HPP */
