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
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template<class T>
	struct iterator_traits {
		typedef typename T::difference_type		difference_type;
		typedef typename T::value_type			value_type;
		typedef typename T::reference			reference;
		typedef typename T::pointer				pointer;
		typedef random_access_iterator_tag		iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef T 							value_type;
		typedef T* 							pointer;
		typedef T& 							reference;
		typedef ptrdiff_t 					difference_type;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Reference	reference;
		typedef Pointer		pointer;
		typedef Category	iterator_category;
	};
} // namespace ft

#endif /* ITERATOR_HPP */
