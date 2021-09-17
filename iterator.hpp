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

	template<class Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*> {
		typedef T 							value_type;
		typedef T* 							pointer;
		typedef T& 							reference;
		typedef std::ptrdiff_t 				difference_type; // check
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class T, class Category = random_access_iterator_tag, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Reference	reference;
		typedef Pointer		pointer;
		typedef Category	iterator_category;
	};

	template<class Iterator>
	class reverse_iterator: public iterator<
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference
					>
	{
		protected:
			Iterator current;
		public:
			typedef Iterator											iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename iterator_traits<Iterator>::value_type		value_type;
			typedef typename iterator_traits<Iterator>::reference		reference;
			typedef typename iterator_traits<Iterator>::pointer			pointer;

			//
			reverse_iterator(): current() {};

	};
} // namespace ft

#endif /* ITERATOR_HPP */
