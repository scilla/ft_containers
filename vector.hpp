#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iterator.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>

namespace ft
{
template <class T>
class vector_iterator: public std::iterator<std::random_access_iterator_tag, T>
{ 
public:
	typedef typename T::difference_type		difference_type;
	typedef typename T::value_type			value_type;
	typedef typename T::reference			reference;
	typedef typename T::pointer				pointer;
	typedef std::random_access_iterator_tag	iterator_category; //or another tag

	vector_iterator();
	vector_iterator(const vector_iterator&);
	~vector_iterator();
};

template <class T, class Alloc = std::allocator<T> >
class vector
{
public:
	typedef T									value_type;
	typedef Alloc								allocator_type;

	typedef typename Alloc::reference			reference;
	typedef typename Alloc::conts_reference		conts_reference;
	typedef typename Alloc::pointer				pointer;
	typedef typename Alloc::const_pointer		const_pointer;
	typedef typename Alloc::difference_type 	difference_type;
    typedef typename Alloc::size_type 			size_type;
	//typedef std::ptrdiff_t						difference_type;
	//typedef size_t								size_type;

	typedef vector_iterator<T>					iterator;
	typedef std::reverse_iterator<iterator>		reverse_iterator;

	// (con|des)tructors
	explicit vector (const allocator_type& alloc = allocator_type()):
	_alloc(alloc),
	_vector(NULL),
	_size(0),
	_capacity(0)
	{}
	explicit vector (unsigned int n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()):
	_alloc(alloc),
	_vector(NULL),
	_size(0),
	_capacity(0)
	{
		_vector = _alloc.allocate(n);
		_capacity = n;
	}
	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type());
	vector (const vector& x);
	~vector();

	// iterators
	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();

	// capacity
	// access
	// modifiers
	// operators
protected:
	iterator		_current;
private:
	pointer			_vector;
	size_type		_size;
	size_type		_capacity;
	allocator_type	_alloc;
};

} // namespace ft

#endif /* VECTOR_HPP */
