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

		//MODIFIERS

		

	private:
		tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;
		size_type		_size;



	}
}