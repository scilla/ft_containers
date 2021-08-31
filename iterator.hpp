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

template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
struct iterator {
	typedef typename T::difference_type		difference_type;
	typedef typename T::value_type			value_type;
	typedef typename T::reference			reference;
	typedef typename T::pointer				pointer;
	typedef std::random_access_iterator_tag	iterator_category;
};

} // namespace ft

#endif /* ITERATOR_HPP */
