#include "vector.hpp"
#include "rbtree.hpp"
#include "map.hpp"
#include "utils.hpp"
#include <stdlib.h>
#include <iostream>
#define fs std::cout

int main(void)
{
	const int range_int[] = {-854, -1, -965, -9, -755};
	const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

	ft::map<int, std::string> ft_map;
	ft_map.print();
	for (int i = 0; i < 10; i++)
	{
		std::cout << "inserting " << (i < 5 ? range_int[i] : i) << std::endl;
		ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
		ft_map.print();
	}
	ft_map.print();
	ft::map<int, std::string>::iterator ft_it_beg = ft_map.begin();
	ft::map<int, std::string>::iterator ft_it_end = ft_map.end();

	for (int i = 0; i < 2; i++)
	{
		ft_it_beg++;
	}
	ft_it_end--;

	ft_map.erase(ft_it_beg, ft_it_end);

	ft::map<int, std::string>::iterator ft_it;
	int i = 0;
	for(ft_it = ft_map.begin(); ft_it != ft_map.end() && i < 200; ++ft_it, ++i)
	{
		if (!(i % 5)) fs << "	";
		fs << "[";
		fs << (*ft_it).first;
		fs << ", ";
		fs << (*ft_it).second;
		fs << "]";
		fs << ", ";
		if ((i % 5) == 4) fs << std::endl;
	}

	ft_map.print();
	return 0;
}
