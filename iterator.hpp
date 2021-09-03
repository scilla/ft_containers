#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>

namespace ft
{
/*
template <class Category, class T, class Distance = std::ptrdiff_t, class T = T*, class Reference = T& >
struct iterator {
	typedef typename T::difference_type		difference_type;
	typedef typename T::value_type			value_type;
	typedef typename T::reference			reference;
	typedef typename T::pointer				pointer;
	typedef std::random_access_iterator_tag	iterator_category;
};
*/

	template<class T>
	class iterator {
		typedef T								iterator_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::value_type			value_type;
		typedef typename T::reference			reference;
		typedef typename T::pointer				pointer;
		typedef std::random_access_iterator_tag	iterator_category;

		explicit iterator(): ptr(NULL) {};

		explicit iterator(iterator_type ptr): ptr(ptr) {}

		template<class Itter>
		iterator(iterator<Itter> const & other) {
			*this = other;
		}
		pointer	base() const {
			return ptr;
		}
		reference operator*() const {
			return *ptr;
		}
		pointer operator->() const {
			return ptr;
		}
		iterator &operator++() {
			++ptr; return *this;
		}
		iterator operator++(int) {
			iterator tmp = *this; ++ptr; return tmp;
		}
		iterator &operator--() {
			--ptr; return *this;
		}
		iterator operator--(int) { 
			iterator tmp = *this; --ptr; return tmp;
		}
		iterator operator-(difference_type val) {
			return iterator(ptr - val);
		}
		iterator operator-(difference_type val) const {
			return iterator(ptr - val);
		}
		pointer	operator-=(difference_type n) {
			ptr -= n;
			return ptr;
		}
		iterator operator+(difference_type val) const {
			return iterator(ptr + val);
		}
		iterator& operator+(iterator<T> &val) const {
			return iterator(ptr + val.ptr);
		}
		pointer	operator+=(difference_type n) {
			ptr += n;
			return ptr;
		}
		reference	operator[](size_t index) {
			return *(ptr + index);
		}
		template <class Iter>
		iterator&	operator=(iterator<Iter> const & other)
		{
			ptr = other.base();
			return *this;
		}
	private:
		iterator_type ptr;
	};

	template <class T, class U>
	ptrdiff_t operator-(const iterator<T> &left,const iterator<U> &right) {
		return left.base() - right.base();
	}

	template <class T, class U>
	ptrdiff_t operator+(const iterator<T> &left,const iterator<U> &right) {
		return left.base() + right.base();
	}

	template <class T, class U>
	iterator<U> operator+(T left, const iterator<U> &right) {
		return right + left;
	}

	template <class T, class U>
	bool operator== (const iterator<T> &left,const iterator<U> &right) {
		return (left.base() == right.base());
	}

	template <class T, class U>
	bool operator!= (const iterator<T> &left,const iterator<U> &right) {
		return !(left == right);
	}

	template <class T, class U>
	bool operator< (const iterator<T> &left,const iterator<U> &right) {
		return (left.base() < right.base());
	}

	template <class T, class U>
	bool operator<= (const iterator<T> &left,const iterator<U> &right) {
		return left.base() <= right.base();
	}

	template <class T, class U>
	bool operator> (const iterator<T> &left,const iterator<U> &right) {
		return (left.base() > right.base());
	}

	template <class T, class U>
	bool operator>= (const iterator<T> &left,const iterator<U> &right) {
		return (left.base() >= right.base());
	}

} // namespace ft

#endif /* ITERATOR_HPP */
