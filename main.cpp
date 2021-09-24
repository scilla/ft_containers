#include "vector.hpp"
#include "rbtree.hpp"
#include "map.hpp"
#include "utils.hpp"
#include <stdlib.h>

int main(void)
{
	const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

	ft::map<int, std::string> ft_map;
	ft::map<int, std::string> ft_mak;

	for (int i = 0; i < 5; i++)
	{
		ft_map.insert(ft::make_pair(i, range_str[i % 5]));
		ft_mak.insert(ft::make_pair(i + 100, range_str[i % 5]));
	}
	//ft_map.erase(7);
	ft_map.print();
	ft_mak.print();

	ft_map.swap(ft_mak);
	
	ft_map.print();
	ft_mak.print();

	ft::map<int, std::string>::iterator ss = ft_map.begin();
	ft::map<int, std::string>::iterator ee = ft_map.end();
	ft_map.erase(ss, ee);
	return 0;
}
