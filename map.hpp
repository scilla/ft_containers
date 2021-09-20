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
	typedef const_rbt_iterator<value_type> 		const_iterator;
	typedef reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef reverse_iterator<iterator>			reverse_iterator;
	typedef Node<value_type>					node_type;
	
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
	explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _comp(comp), _alloc(alloc) {}
	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _comp(comp), _alloc(alloc) {
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
		return iterator(*pt);
	};

	const_iterator begin() const {
		node_type* pt = _tree._root;
		if(!_tree._root)
			return end();
		while (pt->color != FLUO)
			pt--;
		return const_iterator(*pt);
	};

	iterator end() { return iterator(_end); };
	const_iterator end() const { return const_iterator(_end); }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	// capacity
	bool empty() const { return !_size; }
	size_type size() const { return _size; }
	size_type max_size() const { return _alloc.max_size(); } 

	// modifiers
	void clear() {
		remove_bounds();
		_size = 0;
		_tree._nuke(_tree._root);
	}

	ft::pair<iterator, bool> insert(const value_type& value ) {
		remove_bounds();
		node_type* nd = _tree.find(value);
		if (nd)
			return ft::make_pair(iterator(*nd), false);
		nd = &_tree.insert(value);
		add_bounds();
		return ft::make_pair(iterator(*nd), true);
	}

	iterator insert( iterator hint, const value_type& value ) {
		remove_bounds();
		(void)hint;
		node_type* nd = _tree.find(value.first);
		if (nd)
			return iterator(*nd);
		nd = _tree.insert(value);
		add_bounds();
		return iterator(*nd);
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last ) {
		remove_bounds();
		for (; first != last; first++)
			insert(*first);
		add_bounds();
	}

	void erase( iterator pos ) {
		remove_bounds();
		_tree.deleteNode(*pos);
		add_bounds();
	}

	size_type erase (const key_type& k) {
		iterator found = find(k);
		if (found) {
			_tree.deleteNode(found);
			return 1;
		}
		return 0;
	}

	void erase (iterator first, iterator last) {
		for (; first != last; first++)
			erase(*first);
	}

	void swap( map& other ) {
		std::swap(_tree, other._tree);
		std::swap(_start, other._start);
		std::swap(_end, other._end);
		std::swap(_start_ptr, other._start_ptr);
		std::swap(_end_ptr, other._end_ptr);
		std::swap(_comp, other._comp);
		std::swap(_alloc, other._alloc);
		std::swap(_size, other._size);
	}

	// lookup
	size_type count( const Key& key ) const {
		size_type s = 0;
		for (iterator it = begin(); it != end(); it++)
			if ((*it).first == key)
				s++;
		return s;
	}
	iterator find( const Key& key ) {
		return iterator(_tree.find(key));
	}
	const_iterator find( const Key& key ) const {
		return const_iterator(_tree.find(key));
	}
	std::pair<iterator,iterator> equal_range( const Key& key ) {
		return make_pair(lower_bound(key), upper_bound(key));
	}
	std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
		return make_pair(lower_bound(key), upper_bound(key));
	}
	iterator lower_bound( const Key& key ) {
		iterator beg = end();
		beg--;
		while (*beg > key)
			beg--;
		return beg;
	}
	const_iterator lower_bound( const Key& key ) const {
		iterator beg = end();
		beg--;
		while (*beg > key)
			beg--;
		return beg;
	}
	iterator upper_bound( const Key& key ) {
		iterator beg = begin();
		while (*beg <= key)
			beg++;
		return beg;
	}
	const_iterator upper_bound( const Key& key ) const {
		iterator beg = begin();
		while (*beg <= key)
			beg++;
		return beg;
	}

	// observer
	key_compare key_comp() const { return _comp; } // ??
	map::value_compare value_comp() const { return _comp; } // ??
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
