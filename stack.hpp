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

	~stack() {}

	//empty

	bool empty() const {
		return(_container.size() == 0);
	};

	//size

	size_type size() const{
		return(_container.size());
	};

	//top

	reference top() {
		return(*(_container.end() - 1));
	};

	const_reference top() const {
		return(*(_container.end() - 1));
	};

	//push

	void push (const value_type& val){
		_container.push_back(val);
	};

	//pop

	void pop() {
		_container.pop_back();
	};

	friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container == rhs._container; }
	friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container > rhs._container; }

private:
		container_type _container;
};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs > rhs || lhs == rhs);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs > rhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs < rhs);
	}

	
}// namespace ft 

#endif /* STACK_HPP */
