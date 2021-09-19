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


namespace ft {

template <class T>
class map_iterator
{
public:
	typedef T												iterator_type;
	typedef typename iterator_traits<T>::difference_type	difference_type;
	typedef typename iterator_traits<T>::value_type			value_type;
	typedef typename iterator_traits<T>::reference			reference;
	typedef typename iterator_traits<T>::pointer			pointer;
	typedef bidirectional_iterator_tag						iterator_category;

	explicit map_iterator(): _ptr(NULL) {}
	explicit map_iterator(iterator_type ptr): _ptr(ptr) {}
	template<class U>
	map_iterator(const map_iterator<U>& vect): _ptr(vect.base()) { *this = vect; } 
	~map_iterator() {}
	reference operator*() const { return *_ptr; }
	pointer operator->() const { return _ptr; }

	vector_iterator& operator++() {
		++_ptr;
		return *this;
	}
	vector_iterator operator++(int) {
		vector_iterator tmp = *this;
		++_ptr;
		return *this;
	}
	vector_iterator& operator--() {
		--_ptr;
		return *this;
	}
	vector_iterator operator--(int) {
		vector_iterator tmp = *this;
		--_ptr;
		return *this;
	}

	vector_iterator operator-(difference_type n) const {
		return vector_iterator(_ptr - n);
	}
	vector_iterator operator-=(difference_type n) {
		_ptr -= n;
		return _ptr;
	}
	vector_iterator operator+(difference_type n) const {
		return vector_iterator(_ptr + n);
	}
	vector_iterator operator+=(difference_type n) {
		_ptr += n;
		return _ptr;
	}

	reference operator[](size_t i) {
		return (*(_ptr + i));
	}

	template <class K>
	vector_iterator&	operator=(const vector_iterator<K> & other) {
		_ptr = other.base();
		return *this;
	}

	pointer		base() const { return _ptr; }
private:
	pointer		_ptr;
};


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
	typedef map_iterator<value_type>			iterator;
	typedef const map_iterator<const value_type> const_iterator;
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
	explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator());
	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
	~map() {};

	// cose
	map& operator=( const map& other );
	allocator_type get_allocator() const;

	// access
	T& at( const Key& key );
	const T& at( const Key& key ) const;
	T& operator[]( const Key& key );
	T& operator[]( Key&& key );

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
