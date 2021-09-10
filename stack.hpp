#ifndef STACK_HPP
#define STACK_HPP

#include <stack>
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		explicit stack (const container_type& ctnr = container_type()):
			_container(ctnr)
		{}
		

	//empty
	//size
	//top
	//push
	//pop
	private:
		container_type _container;
	};
}// namespace ft 

#endif /* STACK_HPP */
