#include "vector.hpp"
#include "rbtree.hpp"
#include "map.hpp"
#include "set.hpp"
#include "utils.hpp"
#include <stdlib.h>
#include <iostream>
#include <map>
#include <list>
#define fs std::cout
#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
#define T1 int
#define T2 int
typedef TESTED_NAMESPACE::pair<const T1, T2> T3;

struct ft_more {
	bool	operator()(const T1 &first, const T1 &second) const {
		return (first > second);
	}
};

void printVector(TESTED_NAMESPACE::vector<TESTED_TYPE>& vect) {
	for (unsigned int i = 0; i < vect.size(); i++)
		std::cout << vect[i] << std::endl;
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	// std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << (*it).first << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}
int main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(lst_size - i, i));

	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();

	TESTED_NAMESPACE::map<T1, T2> mp_range(it, --(--ite));
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 5;

	it = mp.begin(); ite = --(--mp.end());
	TESTED_NAMESPACE::map<T1, T2> mp_copy(mp);
	for (int i = 0; it != ite; ++it)
		it->second = ++i * 7;

	std::cout << "\t-- PART ONE --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);

	mp = mp_copy;
	mp_copy = mp_range;
	mp_range.clear();

	std::cout << "\t-- PART TWO --" << std::endl;
	printSize(mp);
	printSize(mp_range);
	printSize(mp_copy);
	return (0);

	return 0;
}
