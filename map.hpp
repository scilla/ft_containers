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

template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
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
	explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _start(), _end(), _comp(comp), _alloc(alloc),  _size() { initialize_bounds(); }
	template< class InputIt >
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()): _start(), _end(), _comp(comp), _alloc(alloc) {
		initialize_bounds();
		for (; first != last; first++) {
			_tree.insert(*first);
			_size++;
		}
		add_bounds();
	}

	map(map& new_map): _start(), _end() {
		initialize_bounds();
		*this = new_map;
		add_bounds();
	}

	~map() {}

	void initialize_bounds() {
		_end = (struct Node<value_type>){NULL, NULL, NULL, FLUO, value_type()};
		_start = (struct Node<value_type>){NULL, NULL, NULL, FLUO, value_type()};
		_end_ptr = NULL;
		_start_ptr = NULL;
	}

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
		virtual const char* what() const throw() {
			return "Out of Bound exception";
		}
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
		node_type *res = _tree.find(ft::make_pair(key, T()));
		if (!res)
			return insert(ft::make_pair(key, T())).first->second;
		return res->data.second;
	};

	// iterators

	iterator begin() const {  //da controllare
		if (!_tree._root)
			return end();
		iterator pt = iterator(*_tree._root);
		while (pt.base()->color != FLUO)
			pt--;
		return pt;
	};

	// const_iterator begin() const {
	// 	node_type* pt = _tree._root;
	// 	if(!_tree._root)
	// 		return end();
	// 	while (pt->color != FLUO)
	// 		pt--;
	// 	return const_iterator(*pt);
	// };

	iterator end() const { return iterator(_end); };
	// const_iterator end() const { return iterator(_end); }
	reverse_iterator rbegin() const { return reverse_iterator(end()); }
	// const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
	reverse_iterator rend() const { return reverse_iterator(begin()); }
	// const_reverse_iterator rend() const { return reverse_iterator(begin()); }

	// capacity
	bool empty() const { return !_size; }
	size_type size() const { return _size; }
	size_type max_size() const { return _alloc.max_size()/*_tree.max_size() corretto*/; } //sbagliata bisogna prendere l'allocator dell'rbtree che a sua volta prende quello del nodo type

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
		node_type* nd = _tree.find(value);
		if (nd)
			return iterator(*nd);
		nd = &_tree.insert(value);
		add_bounds();
		return iterator(*nd);
	}

	template< class InputIt >
	void insert( InputIt first, InputIt last, typename enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0 ) {
		remove_bounds();
		for (; first != last; first++)
			insert(*first);
		add_bounds();
	}

	void erase( iterator pos ) {
		remove_bounds();
		_tree.deleteNode(_tree.find(*pos));
		add_bounds();
	}

	size_type erase (const key_type& k) {
		iterator found = find(k);
		if (found != end()) {
			_tree.deleteNode(_tree.find(*found));
			return 1;
		}
		return 0;
	}

	void erase (iterator first, iterator last) {
		for (; first != last; first++)
			erase(first);
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
		for (const_iterator it = begin(); it != end(); it++)
			if ((*it).first == key)
				s++;
		return s;
	}
	iterator find( const Key& key ) {
		return iterator(*_tree.find(ft::make_pair(key, T())));
	}
	const_iterator find( const Key& key ) const {
		return const_iterator(_tree.find(ft::make_pair(key, T())));
	}
	ft::pair<iterator,iterator> equal_range( const Key& key ) {
		return ft::make_pair(iterator(lower_bound(key)), iterator(upper_bound(key)));
	}
	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
		return ft::make_pair(const_iterator(lower_bound(key)), const_iterator(upper_bound(key)));
	}
	iterator lower_bound( const Key& key ) {
		iterator beg = end();
		beg--;
		while ((*beg).first > key)
			beg--;
		return beg;
	}
	const_iterator lower_bound( const Key& key ) const {
		iterator beg = end();
		beg--;
		while ((*beg).first > key)
			beg--;
		return beg;
	}
	iterator upper_bound( const Key& key ) {
		iterator beg = begin();
		while ((*beg).first <= key)
			beg++;
		return beg;
	}
	const_iterator upper_bound( const Key& key ) const {
		iterator beg = begin();
		while ((*beg).first <= key)
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
bool operator==(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs )
{
	return (equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
};

template< class Key, class T, class Compare, class Alloc >
bool operator!=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs ){
	return (!(lhs == rhs));
};

template< class Key, class T, class Compare, class Alloc >
bool operator<(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs )
{
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

template< class Key, class T, class Compare, class Alloc >
bool operator<=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs )
{
	return(!(rhs < lhs));
};

template< class Key, class T, class Compare, class Alloc >
bool operator>(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs )
{
	return (rhs < lhs);
};
template< class Key, class T, class Compare, class Alloc >
bool operator>=(const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs )
{
	return(!(lhs < rhs));
}


}
#endif /* MAP_HPP */
