#include "rbtree.hpp"
#include "utils.hpp"
#include "enable_if.hpp"


namespace ft {

	template < class Key, class Compare = std::less<Key>, class Alloc = std::allocator<const Key> >
	class set {
	public:
		// --- Definitions
		typedef Key													key_type;
		typedef key_type											mapped_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::value_type					value_type;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef typename allocator_type::difference_type			difference_type;

		typedef ft::rbt_iterator<Node<value_type> >				iterator;
		typedef ft::rbt_iterator<Node<value_type> >				const_iterator;
		//typedef ft::rbt_reverse_iterator<iterator>						reverse_iterator;
		//typedef ft::rbt_reverse_iterator<const_iterator>				const_reverse_iterator; non definiti??


		typedef RBTree<value_type, Key>								tree;
		typedef Node<value_type>*									node_ptr;

		//CON|DESTRUCTOR
		explicit set( const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _tree(), _comp(comp), _alloc(alloc), _size(0) {}

		template< class It >
		set( It first, It last, const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _tree(), _comp(comp), _alloc(alloc), _size(0)
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

		iterator insert( iterator hint, const value_type& value ) {
				//non capisco che intenda con punto più vicino se è sorted (?!)
		};

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

		size_type count( const Key& key ) const;

		iterator find( const Key& key );

		const_iterator find( const Key& key ) const;

		std::pair<iterator,iterator> equal_range( const Key& key );

		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

		iterator lower_bound( const Key& key );

		const_iterator lower_bound( const Key& key ) const;

		iterator upper_bound( const Key& key );

		const_iterator upper_bound( const Key& key ) const;

		//OBSERVERS

		key_compare key_comp() const;

		std::set::value_compare value_comp() const;




		

	private:
		tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;
		size_type		_size;



	}
}