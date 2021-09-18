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
	~map_iterator() {}

private:
	pointer _ptr;
};

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
> class map {


};

}

#endif /* MAP_HPP */
