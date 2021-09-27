#ifndef SET_HPP
#define SET_HPP


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

	template < class Key, class Compare = std::less<Key>, class Allocator = std::allocator<const Key> >
	class set {
	public:
		// --- Definitions
		typedef Key													key_type;
		typedef key_type											mapped_type;
		typedef Compare												key_compare;
		typedef Allocator											allocator_type;
		//typedef typename allocator_type::reference					reference;
		//typedef typename allocator_type::const_reference			const_reference;
		//typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::value_type					value_type;
		//typedef typename allocator_type::const_pointer				const_pointer;
		typedef size_t										size_type;
		//typedef typename allocator_type::difference_type			difference_type;

		typedef ft::rbt_iterator<Node<value_type> >				iterator;
		typedef ft::rbt_iterator<Node<value_type> >				const_iterator;
		//typedef ft::rbt_reverse_iterator<iterator>						reverse_iterator;
		//typedef ft::rbt_reverse_iterator<const_iterator>				const_reverse_iterator; non definiti??


		typedef RBTree<value_type, Key>								tree;
		typedef Node<value_type>*									node_ptr;

		//CON|DESTRUCTOR
		explicit set( const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _tree(), _comp(comp), _alloc(alloc), _size(0) {}

		template< class It >
		set( It first, It last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) : _tree(), _comp(comp), _alloc(alloc), _size(0)
		{
			for (; first != last; ++first)
				_tree.insert(*first);
		}

		set( const set& other ): _tree(other._tree), _comp(other._comp), _alloc(other._alloc), _size(other._size) {
			*this = other;
		}

		~set() {
			_tree._nuke(_tree._root);
		}

		allocator_type get_allocator() const {
			return(_alloc);
		};

		//Iterators

		iterator begin() {
			if (!_tree._root)
				return _tree.end();
			return iterator(_tree.getStart());
		}

		const_iterator begin() const {
			if (!_tree._root)
				return _tree._end;
			return iterator(_tree.getStart());
		}

		iterator end() {
			return iterator(_tree.getEnd());
		}

		const_iterator end() const {
			return iterator(_tree.getEnd());
		}

	/*	reverse_iterator rbegin() {
			return reverse_iterator(_tree.getEnd());
		}

		const_reverse_iterator rbegin() const {
			return reverse_iterator(_tree.getEnd());
		}

		reverse_iterator rend() {
			return reverse_iterator(_tree.getStart());
		}

		const_reverse_iterator rend()   const {
			return reverse_iterator(_tree.getStart());
		} */

		// CAPACITY

		bool empty() const {
			return !_size;
		}

		size_type size() const {
			return _size;
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		//MODIFIERS

		void clear() {
			_tree.nuke();
			_size = 0;
		}

		ft::pair<iterator,bool> insert( const value_type& value ) {
			ft::pair<iterator, bool> res = ft::make_pair(iterator(NULL), false);
			_tree.insert(value);
			if(!(res->first = _tree.find(value)))
				res->second = false;
			else
				res->second = true;
			return res;
		};

		//iterator insert( iterator hint, const value_type& value ) {
		//		//non capisco che intenda con punto più vicino se è sorted (?!)
		//};

		void erase( iterator pos ) {
			_tree.remove_bounds();
			_tree.deleteNode(pos);
			_tree.add_bounds();
		};

		void erase( iterator first, iterator last ) {
			iterator todel = first;
			while(first != last)
			{
				erase(first);
				first++;
			}
		};


		void swap( set& other ) {
			std::swap(_tree, other._tree);
			std::swap(_comp, other._comp);
			std::swap(_alloc, other._alloc);
			std::swap(_size, other._size);
		};

		//LOOKUP

		size_type count( const Key& key ) const{
			size_type s = 0;
			for (const_iterator it = begin(); it != end(); it++)
				if ((*it).first == key)
					s++;
			return s;
		};

		iterator find( const Key& key ) {
			return iterator(*_tree.find(key));
		};

		const_iterator find( const Key& key ) const {
			return const_iterator(*_tree.find(key));
		};

		ft::pair<iterator,iterator> equal_range( const Key& key ) {
			return ft::make_pair(iterator(lower_bound(key)), iterator(upper_bound(key)));
		};

		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
			return ft::make_pair(const_iterator(lower_bound(key)), const_iterator(upper_bound(key)));

		};

		iterator lower_bound( const Key& key ) {
			iterator beg = end();
			beg--;
			while ((*beg).first > key)
				beg--;
			return beg;
		};

		const_iterator lower_bound( const Key& key ) const {
			iterator beg = end();
			beg--;
			while ((*beg).first > key)
				beg--;
			return beg;
		};

		iterator upper_bound( const Key& key ) {
			iterator beg = begin();
			while ((*beg).first <= key)
				beg++;
			return beg;	
		};

		const_iterator upper_bound( const Key& key ) const {
			iterator beg = begin();
			while ((*beg).first <= key)
				beg++;
			return beg;
		};

		//OBSERVERS

		//key_compare key_comp() const {}; //BOH

		//set::value_compare value_comp() const {}; //BOH






		

	private:
		tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;
		size_type		_size;



	};


	//OPERATOR OVERLOADS

	template <typename Key, typename Compare>
	void swap(ft::set<Key, Compare> &x, ft::set<Key, Compare> &y)
	{
		x.swap(y);
	}

	template <class Key, class Compare, class Alloc>
	bool operator== (const ft::set<Key,Compare,Alloc> & lhs, const ft::set<Key,Compare,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class Compare, class Alloc>
	bool operator!= (const ft::set<Key,Compare,Alloc> & lhs, const ft::set<Key,Compare,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class Compare, class Alloc>
	bool operator<  (const ft::set<Key,Compare,Alloc> & lhs, const ft::set<Key,Compare,Alloc> & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class Compare, class Alloc>
	bool operator<= (const ft::set<Key,Compare,Alloc> & lhs, const ft::set<Key,Compare,Alloc> & rhs)
	{
		return !(rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>  (const ft::set<Key,Compare,Alloc> & lhs, const ft::set<Key,Compare,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>= (const ft::set<Key,Compare,Alloc> & lhs, const ft::set<Key,Compare,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif /* SET_HPP */
