#include "vector.hpp"
#include "rbtree.hpp"
#include "map.hpp"
#include "utils.hpp"
#include <stdlib.h>

int main(void)
{
	const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

	ft::map<int, std::string> ft_map;

	for (int i = 0; i < 100; i++)
	{
		ft_map.insert(ft::make_pair(i, range_str[i % 5]));
	}

	ft_map.print();

	return 0;
}
