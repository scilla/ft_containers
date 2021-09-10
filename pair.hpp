#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template <class T, class U>
struct pair
{
	typedef T first_type;
	typedef U second_type;

	T first;
	U second;

	pair() : first(), second() {};
	pair (const first_type& a, const second_type& b) : first(a), second(b) {};

	template<class U, class V>
	pair (const pair<U,V>& pr): first(pr.first), second(pr.second) {}

	pair& operator=(const pair& pr) {
		first = pr.first;
		second = pr.second;
		return *this;
	}
};

template <class T, class U>
bool operator== (const pair<T,U>& lhs, const pair<T,U>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

template <class T, class U>
bool operator!= (const pair<T,U>& lhs, const pair<T,U>& rhs)
{ return !(lhs==rhs); }

template <class T, class U>
bool operator<  (const pair<T,U>& lhs, const pair<T,U>& rhs)
{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

template <class T, class U>
bool operator<= (const pair<T,U>& lhs, const pair<T,U>& rhs)
{ return !(rhs<lhs); }

template <class T, class U>
bool operator>  (const pair<T,U>& lhs, const pair<T,U>& rhs)
{ return rhs<lhs; }

template <class T, class U>
bool operator>= (const pair<T,U>& lhs, const pair<T,U>& rhs)
{ return !(lhs<rhs); }

#endif /* PAIR_HPP */
