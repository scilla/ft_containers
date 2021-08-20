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
template <class T, bool reverse = false>
class vector_iterator { 
public:
	typedef typename T::difference_type		difference_type;
	typedef typename T::value_type			value_type;
	typedef typename T::reference			reference;
	typedef typename T::pointer				pointer;
	typedef std::random_access_iterator_tag	iterator_category; //or another tag

	iterator();
	iterator(const iterator&);
	~iterator();

	iterator& operator=(const iterator&);
	bool operator==(const iterator&) const;
	bool operator!=(const iterator&) const;
	bool operator<(const iterator&) const; //optional
	bool operator>(const iterator&) const; //optional
	bool operator<=(const iterator&) const; //optional
	bool operator>=(const iterator&) const; //optional

	iterator& operator++();
	iterator operator++(int); //optional
	iterator& operator--(); //optional
	iterator operator--(int); //optional
	iterator& operator+=(size_type); //optional
	iterator operator+(size_type) const; //optional
	friend iterator operator+(size_type, const iterator&); //optional
	iterator& operator-=(size_type); //optional            
	iterator operator-(size_type) const; //optional
	difference_type operator-(iterator) const; //optional

	reference operator*() const;
	pointer operator->() const;
	reference operator[](size_type) const; //optional
};

template <class T, class Alloc = std::allocator<T> >
class vector
{
private:
public:
	typedef T									value_type;
	typedef Alloc								allocator_type;
	typedef typename Alloc::reference			reference;
	typedef typename Alloc::conts_reference		conts_reference;
	typedef typename Alloc::pointer				pointer;
	typedef typename Alloc::const_pointer		const_pointer;
	typedef typename Alloc::difference_type 	difference_type;
    typedef typename Alloc::size_type 			size_type;

	typedef vector_iterator<T>					iterator;
	typedef const vector_iterator<T>			const_iterator;
	typedef vector_iterator<T, true>			iterator;
	typedef const vector_iterator<T, true>		const_iterator;


	// (con|des)tructors
	explicit vector (const allocator_type& alloc = allocator_type());
	explicit vector (unsigned int n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type());
	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type());
	vector (const vector& x);
	~vector();

	// capacity
	// access
	// modifiers
};

} // namespace ft

#endif /* VECTOR_HPP */
