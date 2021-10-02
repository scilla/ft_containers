#include "vector.hpp"
#include "rbtree.hpp"
#include "map.hpp"
#include "set.hpp"
#include "utils.hpp"
#include <stdlib.h>
#include <iostream>
#include <map>
#define fs std::cout


#define T1 int
#define T2 std::string

struct ft_more {
	bool	operator()(const T1 &first, const T1 &second) const {
		return (first > second);
	}
};

int main(void)
{
	int range_int[] = {-351, -999, -5, -76, 101};
	std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};


	ft::map<int, std::string, ft_more> ft_map;
	std::map<int, std::string, ft_more> stl_map;
	for (int i = 0; i < 101; i++)
	{
		stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
		ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
	}
	// if (stl_map.lower_bound(k)->first != ft_map.lower_bound(k)->first)
	// 	std::cout << " discr " << k << std::endl;
	// if (stl_map.upper_bound(k)->first != ft_map.upper_bound(k)->first)
	// 	std::cout << " discr " << k << std::endl;
		ft_map.print();
	std::cout << " stl lower> " << stl_map.lower_bound(101)->first << std::endl;
	std::cout << " ft lower > " << ft_map.lower_bound(101)->first << std::endl;
	std::cout << " stl upper> " << stl_map.upper_bound(101)->first << std::endl;
	std::cout << " ft upper > " << ft_map.upper_bound(101)->first << std::endl;
	ft::map<int, std::string, ft_more>::iterator ft_it;
	int i = 0;
	for(ft_it = ft_map.begin(); ft_it != ft_map.end() && i < 100; ++ft_it, ++i)
	{
		if (!(i % 5)) fs << "	";
		fs << "[";
		fs << (*ft_it).first;
		fs << ", ";
		fs << (*ft_it).second;
		fs << "]";
		fs << ", ";
		if ((i % 5) == 4 || 1) fs << std::endl;
	}

	return 0;
}
