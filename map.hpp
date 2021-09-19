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
#include "utils.hpp"
#include "enable_if.hpp"
#include <stdio.h>
#include "rbtree.hpp"
#include "pair.hpp"

namespace ft {

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T> > >
class map {
public:
	typedef typename Key						key_type;
	typedef typename T							mapped_key;
	typedef typename ft::pair<const Key, T>		value_type;
	typedef size_t								size_type;
	typedef ptrdiff_t							difference_type;
	typedef Compare								key_compare;
	typedef Allocator							allocator_type;
	typedef value_type&							reference;
	typedef const reference						const_reference;
	typedef typename Allocator::pointer			pointer;
	typedef typename Allocator::const_pointer	const_pointer;
	typedef rbt_iterator<value_type>			iterator;
	typedef const rbt_iterator<const value_type> const_iterator;
	typedef reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef reverse_iterator<iterator>			reverse_iterator;
	
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
		}
	}
	map(map& new_map) {
		*this = new_map;
	}
	~map() {}

	// cose
	map& operator=( const map& other ) {
		_tree = other._tree;
		_comp = other._comp;
		_alloc = other._alloc;
		_size = other._size;
		return *this;
	}
	allocator_type get_allocator() const { return _alloc; }

	// access
	T& at( const Key& key ) {
		struct node<value_type> *res = _tree.find(key);
		if (!res)
			/* exception */ ;
		return res->data->second;
	}
	const T& at( const Key& key ) const {
		struct node<value_type> *res = _tree.find(key);
		if (!res)
			/* exception */ ;
		return res->data->second;
	}
	T& operator[]( const Key& key );

	// iterators
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;

	// capacity
	bool empty() const;
	size_type size() const;
	size_type max_size() const;

	// modifiers
	void clear();
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
	RBTree<value_type>		_tree;
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
