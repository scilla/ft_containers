#include "vector.hpp"
#include "rbtree.hpp"
#include "map.hpp"
#include "set.hpp"
#include "utils.hpp"
#include <stdlib.h>
#include <iostream>
#include <map>
#define fs std::cout
#define TESTED_TYPE int
#define TESTED_NAMESPACE ft
#define T1 int
#define T2 std::string

struct ft_more {
	bool	operator()(const T1 &first, const T1 &second) const {
		return (first > second);
	}
};

void printVector(TESTED_NAMESPACE::vector<TESTED_TYPE>& vect) {
	for (unsigned int i = 0; i < vect.size(); i++)
		std::cout << vect[i] << std::endl;
}

int main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it = vct.rbegin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_reverse_iterator ite = vct.rbegin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;

	printVector(vct);
	it = it + 5;
	printVector(vct);
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	printVector(vct);
	*(it += 2) = 21;
	printVector(vct);

	std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;
	// std::map<int, std::string, ft_more> stl_map;
	// for (int i = 0; i < 101; i++)
	// {
	// 	stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
	// 	ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
	// }
	// 	ft_map.print();
	// std::cout << " stl lower> " << stl_map.lower_bound(101)->first << std::endl;
	// std::cout << " ft lower > " << ft_map.lower_bound(101)->first << std::endl;
	// std::cout << " stl upper> " << stl_map.upper_bound(101)->first << std::endl;
	// std::cout << " ft upper > " << ft_map.upper_bound(101)->first << std::endl;
	// ft::map<int, std::string, ft_more>::iterator ft_it;
	// int i = 0;
	// for(ft_it = ft_map.begin(); ft_it != ft_map.end() && i < 100; ++ft_it, ++i)
	// {
	// 	if (!(i % 5)) fs << "	";
	// 	fs << "[";
	// 	fs << (*ft_it).first;
	// 	fs << ", ";
	// 	fs << (*ft_it).second;
	// 	fs << "]";
	// 	fs << ", ";
	// 	if ((i % 5) == 4 || 1) fs << std::endl;
	// }

	return 0;
}
