#ifndef UTILS_HPP
#define UTILS_HPP
#include <iostream>

namespace ft
{

template<typename T, typename U, typename R>
struct binary_function
{
	typedef T 	first_argument_type; 
	typedef U 	second_argument_type;
	typedef R 	result_type;
};

template<typename T>
struct less: public ft::binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y) const {
		return x < y;
	}
};

template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
{
	while (first1!=last1)
	{
		if (first2 == last2 || *first2 < *first1) 
			return false;
		else if (*first1 < *first2) 
			return true;
		++first1;
		++first2;
	}
	return (first2!=last2);
}

template <class InputIterator1, class InputIterator2>
bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
{
	while (lit != lend)
	{
		if (rit == rend || *rit != *lit)
			return (false);
		++lit, ++rit;
	}
	return (rit == rend);
}

}

#endif
