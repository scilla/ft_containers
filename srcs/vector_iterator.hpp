#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP
#include <utility>
#include "iterator.hpp"
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <algorithm>
#include "utils.hpp"
#include "enable_if.hpp"
#include <stdio.h>
#include <string.h>

namespace ft
{
template <class T>
class vector_iterator
{
	public:
		typedef T								iterator_type;
		typedef T								value_type;
		typedef T*								iterator_value;
		typedef T&								reference;
		typedef T*								pointer;
		typedef std::ptrdiff_t					difference_type; // std:: cause linux
		typedef random_access_iterator_tag		iterator_category;

		explicit	vector_iterator(): _ptr(NULL) {};
		explicit vector_iterator(T& newnode): _ptr(newnode) {}
		explicit vector_iterator(const T& newnode): _ptr(newnode) {}
		explicit vector_iterator(const pointer newnode): _ptr(newnode) {}

		vector_iterator(const vector_iterator& newit): _ptr(NULL) { *this = newit; } 
		~vector_iterator() {}

		reference operator*() const { return *_ptr; }
		pointer operator->() const { return _ptr; }

		vector_iterator& operator++() {
			++_ptr;
			return *this;
		}
		vector_iterator operator++(int) {
			vector_iterator tmp = *this;
			++_ptr;
			return tmp;
		}
		vector_iterator& operator--() {
			--_ptr;
			return *this;
		}
		vector_iterator operator--(int) {
			vector_iterator tmp = *this;
			--_ptr;
			return tmp;
		}

		vector_iterator operator-(difference_type n) const {
			return vector_iterator(_ptr - n);
		}
		vector_iterator operator-=(difference_type n) {
			_ptr -= n;
			return vector_iterator(_ptr);
		}
		vector_iterator operator+(difference_type n) const {
			return vector_iterator(_ptr + n);
		}
		vector_iterator operator+=(difference_type n) {
			_ptr += n;
			return vector_iterator(_ptr);
		}

		reference operator[](size_t i) {
			return reference(*(_ptr + i));
		}

		template <class K>
		vector_iterator&	operator=(vector_iterator<K> const& other) const{
			_ptr = other.base();
			return *this;
		}

		template <class K>
		vector_iterator&	operator=(vector_iterator<K> const& other) {
			_ptr = other.base();
			return *this;
		}

		template <class K>
		vector_iterator& operator=(const K& other) {
			_ptr = other.base();
			return *this;
		}

		template <class K>
		int operator-(K& other) {
			return base() - other.base();
		}

		pointer		base() { return _ptr; }
		const pointer		base() const { return _ptr; }
	private:
		pointer		_ptr;
};

template <class T, class U>
std::ptrdiff_t operator-(const vector_iterator<T>& left, const vector_iterator<U>& right) {
	return (left.base() - right.base());
}
template <class T, class U>
bool operator== (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() == right.base()); }
template <class T, class U>
bool operator!= (const vector_iterator<T>& left,const vector_iterator<U>& right) { return !(left == right); }
template <class T, class U>
bool operator< (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() < right.base()); }
template <class T, class U>
bool operator<= (const vector_iterator<T>& left,const vector_iterator<U>& right) { return left.base() <= right.base(); }
template <class T, class U>
bool operator> (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() > right.base()); }
template <class T, class U>
bool operator>= (const vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() >= right.base()); }

template <class T>
class const_vector_iterator
{
	public:
		typedef const T								iterator_type;
		typedef const T*							iterator_value;
		typedef T									value_type;
		typedef T&									reference;
		typedef const T&							const_reference;
		typedef T*									pointer;
		typedef const T*							const_pointer;
		typedef std::ptrdiff_t						difference_type; // std:: cause linux
		typedef random_access_iterator_tag			iterator_category;

		explicit	const_vector_iterator(): _ptr(NULL) {};
		explicit const_vector_iterator(T& newnode): _ptr(newnode) {}
		explicit const_vector_iterator(const T& newnode): _ptr(newnode) {}
		explicit const_vector_iterator(const pointer newnode): _ptr(newnode) {}

		const_vector_iterator(const const_vector_iterator& newit): _ptr(NULL) { *this = newit; } 

		template<class Iter>
		const_vector_iterator(const Iter& newit): _ptr(NULL) { *this = newit; } 
		~const_vector_iterator() {}

		const_reference operator*() const { return *_ptr; }
		const_pointer operator->() const { return _ptr; }

		const_vector_iterator& operator++() {
			++_ptr;
			return *this;
		}
		const_vector_iterator operator++(int) {
			const_vector_iterator tmp = *this;
			++_ptr;
			return tmp;
		}
		const_vector_iterator& operator--() {
			--_ptr;
			return *this;
		}
		const_vector_iterator operator--(int) {
			const_vector_iterator tmp = *this;
			--_ptr;
			return tmp;
		}

		const_vector_iterator operator-(difference_type n) const {
			return const_vector_iterator(_ptr - n);
		}
		const_vector_iterator operator-=(difference_type n) {
			_ptr -= n;
			return const_vector_iterator(_ptr);
		}
		const_vector_iterator operator+(difference_type n) const {
			return const_vector_iterator(_ptr + n);
		}
		const_vector_iterator operator+=(difference_type n) {
			_ptr += n;
			return const_vector_iterator(_ptr);
		}

		const_reference operator[](size_t i) {
			return const_reference(*(_ptr + i));
		}

		template <class K>
		const_vector_iterator&	operator=(const_vector_iterator<K> const& other) const{
			_ptr = other.base();
			return *this;
		}

		template <class K>
		const_vector_iterator&	operator=(K const& other) {
			_ptr = other.base();
			return *this;
		}

		template <class K>
		int operator-(K& other) {
			return base() - other.base();
		}

		pointer		base() { return _ptr; }
		const pointer		base() const { return _ptr; }
	private:
		pointer		_ptr;
};

template <class T, class U>
std::ptrdiff_t operator-(const const_vector_iterator<T>& left, const vector_iterator<U>& right) {
	return (left.base() - right.base());
}
template <class T, class U>
const_vector_iterator<U> operator+(T left, const vector_iterator<U>& right) { 
	return (right + left);
}
template <class T, class U>
bool operator== (const const_vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() == right.base()); }
template <class T, class U>
bool operator!= (const const_vector_iterator<T>& left,const vector_iterator<U>& right) { return !(left == right); }
template <class T, class U>
bool operator< (const const_vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() < right.base()); }
template <class T, class U>
bool operator<= (const const_vector_iterator<T>& left,const vector_iterator<U>& right) { return left.base() <= right.base(); }
template <class T, class U>
bool operator> (const const_vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() > right.base()); }
template <class T, class U>
bool operator>= (const const_vector_iterator<T>& left,const vector_iterator<U>& right) { return (left.base() >= right.base()); }

template <class T, class U>
std::ptrdiff_t operator-(const const_vector_iterator<T>& left, const const_vector_iterator<U>& right) {
	return (left.base() - right.base());
}
template <class T, class U>
const_vector_iterator<U> operator+(T left, const const_vector_iterator<U>& right) { 
	return (right + left);
}
template <class T, class U>
bool operator== (const const_vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() == right.base()); }
template <class T, class U>
bool operator!= (const const_vector_iterator<T>& left,const const_vector_iterator<U>& right) { return !(left == right); }
template <class T, class U>
bool operator< (const const_vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() < right.base()); }
template <class T, class U>
bool operator<= (const const_vector_iterator<T>& left,const const_vector_iterator<U>& right) { return left.base() <= right.base(); }
template <class T, class U>
bool operator> (const const_vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() > right.base()); }
template <class T, class U>
bool operator>= (const const_vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() >= right.base()); }

template <class T, class U>
std::ptrdiff_t operator-(const vector_iterator<T>& left, const const_vector_iterator<U>& right) {
	return (left.base() - right.base());
}
template <class T, class U>
vector_iterator<U> operator+(T left, const const_vector_iterator<U>& right) { 
	return (right + left);
}
template <class T, class U>
bool operator== (const vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() == right.base()); }
template <class T, class U>
bool operator!= (const vector_iterator<T>& left,const const_vector_iterator<U>& right) { return !(left == right); }
template <class T, class U>
bool operator< (const vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() < right.base()); }
template <class T, class U>
bool operator<= (const vector_iterator<T>& left,const const_vector_iterator<U>& right) { return left.base() <= right.base(); }
template <class T, class U>
bool operator> (const vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() > right.base()); }
template <class T, class U>
bool operator>= (const vector_iterator<T>& left,const const_vector_iterator<U>& right) { return (left.base() >= right.base()); }

} // namespace ft
#endif /* VECTOR_ITERATOR_HPP */
