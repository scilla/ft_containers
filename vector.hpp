#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>

namespace ft
{
template <class T>
class vector_iterator
{
private:
public:
	vector_iterator();
	~vector_iterator();
};

template <class T, class Alloc = std::allocator<T> >
class vector
{
private:
public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::conts_reference	conts_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;

	// (con|des)tructors
	explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (unsigned int n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type());
	vector (const vector& x);
	~vector();

	// iterators
	// capacity
	// access
	// modifiers
};

} // namespace ft

#endif /* VECTOR_HPP */
