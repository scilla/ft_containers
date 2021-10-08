#include <map>

#include "tester.hpp"
#include "../../srcs/map.hpp"

#define SIZE 100000

template <class Ta, class Tb>
std::string equalContent(
	const std::map<Ta, Tb> & stl_map,
	const ft::map<Ta, Tb> & ft_map
)
{
	typename ft::map<Ta, Tb>::const_iterator ft_it;
	typename std::map<Ta, Tb>::const_iterator stl_it;
	if (ft_map.size() != stl_map.size())
		return ("✘");
	stl_it = stl_map.begin();
	for(ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++)
	{
		if ((*ft_it).first != (*stl_it).first || (*ft_it).second != (*stl_it).second)
			return ("✘");
		stl_it++;
	}
	return ("✔");
}

template <class Ta, class Tb>
bool printMapAttributes(
	std::fstream& fs,
	std::map<Ta, Tb>& stl_map,
	ft::map<Ta, Tb>& ft_map
)
{
	/* STL Values */
	std::string stl_empty = ((stl_map.empty() == 1) ? "true" : "false");
	size_t stl_size = stl_map.size();
	size_t stl_max_size = stl_map.max_size();

	/* FT Values */
	std::string ft_empty = ((ft_map.empty() == 1) ? "true" : "false");
	size_t ft_size = ft_map.size();
	size_t ft_max_size = ft_map.max_size();

	/* FT Result compare values */
	bool empty = equalbool(ft_empty, stl_empty);
	bool size = equalbool(ft_size, stl_size);
	bool max_size = equalbool(ft_max_size, stl_max_size);
	std::string content = equalContent(stl_map, ft_map);

	fs << "\n══════════════════════════════════════════════════════════════\n";
	fs << "maps attributes : \n";
	fs << "STL : \n";
	fs << "Empty       : " << stl_empty  << std::endl;
	fs << "Size        : " << stl_size  << std::endl;
	fs << "Max size    : " << stl_max_size  << std::endl;
	fs << "Content     : [\n";

	typename std::map<Ta, Tb>::iterator stl_it;
	int i = 0;
	for (stl_it = stl_map.begin();  stl_it != stl_map.end() && i < 200; ++stl_it, ++i)
	{
		if (!(i % 5)) fs << "	";
		fs << "[";
		fs << (*stl_it).first;
		fs << ", ";
		fs << (*stl_it).second;
		fs << "]";
		fs << ", ";
		if ((i % 5) == 4) fs << std::endl;
	}
	fs << (i == 20 ? "	..." : "") << "\n]\n";

	fs << std::endl;

	fs << "FT : \n";
	fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
	fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;
	fs << "Max size [" << equal(ft_max_size, stl_max_size) << "]: " << ft_max_size  << std::endl;

	fs << "Content  [" << content << "]: [\n";

	typename ft::map<Ta, Tb>::iterator ft_it;
	i = 0;
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
	fs << (i == 20 ? "	..." : "") << "\n]\n";

	fs << "══════════════════════════════════════════════════════════════\n";

	/* Error case */
	if (empty == false)
		return (false);
	else if (size == false)
		return (false);
	else if (max_size == false)
		return (false);
	else if (content == "✘")
		return (false);
	return (true);
}

void test_map()
{

	std::cout << UNDERLINE << BLUE << "MAP :\n" << NORMAL ;

	mkdir("./tester/maps_output", 0777);

	std::fstream fs;

	/* Constructors */
	std::cout << YELLOW"Constructors : \n" << NRM;
	fs.open("./tester/maps_output/constructor", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Default constructor */
	{
		start_stl();
		std::map<int, std::string> stl_default_map;
		stop_stl();
		start_ft();
		ft::map<int, std::string> ft_default_map;
		stop_ft();

		fs.open("./tester/maps_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_default_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_default_map;\n";
		std::cout << std::setw(30) << std::left << "Default constructor: " << std::setw(0) <<((printMapAttributes(fs, stl_default_map, ft_default_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Range constrcutor */
	{
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		std::map<int, std::string> stl_map_copy(stl_map.begin(), stl_map.end());
		stop_stl();
		start_ft();
		ft::map<int, std::string> ft_map_copy(ft_map.begin(), ft_map.end());
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i, range_str[i % 5]));\n";
		fs << "ft::map<int, std::string> ft_map_copy(ft_map.begin(), ft_map.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i, range_str[i % 5]));\n";
		fs << "std::map<int, std::string> stl_map_copy(stl_map.begin(), stl_map.end());\n";
		std::cout << std::setw(30) << std::left << "Range constructor: " << std::setw(0) << ((printMapAttributes(fs, stl_map_copy, ft_map_copy) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Copy constructor */
	{
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		std::map<int, std::string> stl_map_copy(stl_map);
		stop_stl();
		start_ft();
		ft::map<int, std::string> ft_map_copy(ft_map);
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i, range_str[i % 5]));\n";
		fs << "ft::map<int, std::string> ft_map_copy(ft_map);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i, range_str[i % 5]));\n";
		fs << "std::map<int, std::string> stl_map_copy(stl_map);\n";
		std::cout << std::setw(30) << std::left << "Copy constructor: " << std::setw(0) << ((printMapAttributes(fs, stl_map_copy, ft_map_copy) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Assign operator */
	{
		const int range_int[] = {1478, 1952, 1242, -96, -9};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 1000; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);


		std::map<int, std::string> stl_map_copy;
		ft::map<int, std::string> ft_map_copy;

		start_stl();
		stl_map_copy = stl_map;
		stop_stl();
		start_ft();
		ft_map_copy = ft_map;
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1478, 1952, 1242, -96, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 1000; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "ft::map<int, std::string> ft_map_copy = ft_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1478, 1952, 1242, -96, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 1000; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "std::map<int, std::string> stl_map_copy = stl_map;\n";
		std::cout << std::setw(30) << std::left << "Operator = : " << std::setw(0) << ((printMapAttributes(fs, stl_map_copy, ft_map_copy) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << YELLOW"Iterators : \n" << NRM;
	fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();

	/* Begin */
	{
		const int range_int[] = {1485, 5, 89, 652, -94};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);


		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1485, 5, 89, 652, -94};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1485, 5, 89, 652, -94};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		std::cout << std::setw(30) << std::left << "Begin: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_map.begin()).first, (*ft_map.begin()).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_map.begin()).second, (*ft_map.begin()).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const begin */
	{
		const int range_int[] = {48, 9, 12, 63, 99};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::const_iterator stl_it = stl_map.begin();
		ft::map<int, std::string>::const_iterator ft_it = ft_map.begin();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {48, 9, 12, 63, 99};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.begin();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {48, 9, 12, 63, 99};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.begin();\n";
		std::cout << std::setw(30) << std::left << "Const begin: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* End */
	{
		const int range_int[] = {-99, 584, 965, 366, 77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::iterator stl_it = stl_map.end();
		ft::map<int, std::string>::iterator ft_it = ft_map.end();

		--stl_it;
		--ft_it;

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.end();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.end();\n";
		fs << "--stl_it;\n";
		std::cout << std::setw(30) << std::left << "End: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const end */
	{
		const int range_int[] = {154, 966, 3, -84, 75};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::const_iterator stl_it = stl_map.end();
		ft::map<int, std::string>::const_iterator ft_it = ft_map.end();

		--stl_it;
		--ft_it;

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {154, 966, 3, -84, 75};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.end();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {154, 966, 3, -84, 75};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.end();\n";
		fs << "--stl_it;\n";
		std::cout << std::setw(30) << std::left << "Const end: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Reverse begin */
	{
		const int range_int[] = {1458, -985, 58, 632, 65};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::reverse_iterator stl_it = stl_map.rbegin();
		ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rbegin();

		++stl_it;
		++ft_it;

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1458, -985, 58, 632, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rbegin();\n";
		fs << "++ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1458, -985, 58, 632, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::reverse_iterator stl_it = stl_map.rbegin();\n";
		fs << "++stl_it;\n";
		std::cout << std::setw(30) << std::left << "Reverse begin: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const reverse begin */
	{
		const int range_int[] = {859, 99, -325, -65, -98};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rbegin();
		ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rbegin();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {859, 99, -325, -65, -98};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rbegin();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {859, 99, -325, -65, -98};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rbegin();\n";
		std::cout << std::setw(30) << std::left << "Const reverse begin: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Reverse end */
	{
		const int range_int[] = {325, -657, -942, -8, 66};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::reverse_iterator stl_it = stl_map.rend();
		ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rend();

		--stl_it;
		--ft_it;

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {325, -657, -942, -8, 66};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::reverse_iterator ft_it = ft_map.rend();\n";
		fs << "--ft_it;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {325, -657, -942, -8, 66};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::reverse_iterator stl_it = stl_map.rend();\n";
		fs << "--stl_it;\n";
		std::cout << std::setw(30) << std::left << "Reverse end: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}


	/* Const reverse end */
	{
		const int range_int[] = {-99, 584, 965, 366, 77};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/iterators", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rend();
		ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rend();

		--(--stl_it);
		--(--ft_it);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_reverse_iterator ft_it = ft_map.rend();\n";
		fs << "--(--ft_it);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-99, 584, 965, 366, 77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_reverse_iterator stl_it = stl_map.rend();\n";
		fs << "--(--stl_it);\n";
		std::cout << std::setw(30) << std::left << "Const reverse end: " << std::setw(0) << "[";
		std::cout << "maps: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << YELLOW"Capacity : \n" << NRM;
	fs.open("./tester/maps_output/capacity", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();

	/* Empty true */
	{
		std::map<int, std::string> stl_default_map;
		ft::map<int, std::string> ft_default_map;

		fs.open("./tester/maps_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_default_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_default_map;\n";
		std::cout << std::setw(30) << std::left << "Empty true: " << std::setw(0) << ((printMapAttributes(fs, stl_default_map, ft_default_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printBoolResult(fs, stl_default_map.empty(), ft_default_map.empty()) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Empty false */
	{
		const int range_int[] = {1452, 3651, -98, 84, 899};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {1452, 3651, -98, 84, 899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		std::cout << std::setw(30) << std::left << "Empty false: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printBoolResult(fs, stl_map.empty(), ft_map.empty()) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Size */
	{
		const int range_int[] = {9, -84, -45, -67, -9};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {9, -84, -45, -67, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "Sending output...\n";
		fs << "ft_map.insert(ft::make_pair(42, \"Represent\"));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {9, -84, -45, -67, -9};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "Sending output...\n";
		fs << "stl_map.insert(std::make_pair(42, \"Represent\"));\n";
		std::cout << std::setw(30) << std::left << "Size: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "[";
		std::cout << ((printSingleValue(fs, stl_map.size(), ft_map.size()) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");

		stl_map.insert(std::make_pair(42, "Represent"));
		ft_map.insert(ft::make_pair(42, "Represent"));

		std::cout << ((printSingleValue(fs, stl_map.size(), ft_map.size()) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");

		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Maximum size */
	{
		std::map<int, std::string> stl_default_map;
		ft::map<int, std::string> ft_default_map;

		fs.open("./tester/maps_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_default_map;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_default_map;\n";
		std::cout << std::setw(30) << std::left << "Maximum size: " << std::setw(0) << ((printMapAttributes(fs, stl_default_map, ft_default_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, stl_default_map.max_size(), ft_default_map.max_size()) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << YELLOW"Element access : \n" << NRM;
	fs.open("./tester/maps_output/access", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Operator [] */
	{
		const int range_int[] = {-1489, -98, -9, -46, -256};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/access", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-1489, -98, -9, -46, -256};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "Sending output...\n";
		fs << "ft_map[-9] = \"Changed\";\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-1489, -98, -9, -46, -256};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "Sending output...\n";
		fs << "stl_map[-9] = \"Changed\";\n";
		std::cout << std::setw(30) << std::left << "Operator []: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "[";
		std::cout << ((printSingleValue(fs, stl_map[-9], ft_map[-9]) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");

		start_stl();
		stl_map[-9] = "Changed";
		stop_stl();
		start_ft();
		ft_map[-9] = "Changed";
		stop_ft();
		std::cout << ((printSingleValue(fs, stl_map[-9], ft_map[-9]) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]";
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << YELLOW"Modifier : \n" << NRM;
	fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Insert single */
	{
		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;


		start_stl();
		for (int i = 0; i < SIZE; ++i)
			stl_map.insert(std::make_pair(i, "Mattie"));
		stop_stl();
		start_ft();
		for (int i = 0; i < SIZE; ++i)
			ft_map.insert(ft::make_pair(i, "Mattie"));
		stop_ft();
		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; ++i)\n";
		fs << "	ft_map.insert(ft::make_pair(i, \"Mattie\"));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; ++i)\n";
		fs << "	stl_map.insert(std::make_pair(i, \"Mattie\"));\n";
		std::cout << std::setw(30) << std::left << "Insert: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Insert hint */
	{
		const int range_int[] = {584, 96, 21, -54, 36};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		stl_map.insert(++(stl_map.begin()), std::make_pair(42, "Nice"));
		stop_stl();
		start_ft();
		ft_map.insert(++(ft_map.begin()), ft::make_pair(42, "Nice"));
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {584, 96, 21, -54, 36};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "ft_map.insert(++(ft_map.begin()), ft::make_pair(42, \"Nice\"));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {584, 96, 21, -54, 36};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "stl_map.insert(++(stl_map.begin()), std::make_pair(42, \"Nice\"));\n";
		std::cout << std::setw(30) << std::left << "Insert hint: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Insert Range */
	{
		const int range_int[] = {754, -985, 58, 999, 5};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map_one;
		ft::map<int, std::string> ft_map_one;
		std::map<int, std::string> stl_map_two;
		ft::map<int, std::string> ft_map_two;

		for (int i = 0; i < 5; i++)
		{
			stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));
			stl_map_two.insert(std::make_pair(range_int[i] + 266, range_str[i] + "_two"));
			ft_map_two.insert(ft::make_pair(range_int[i] + 266, range_str[i] + "_two"));
		}

		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		stl_map_one.insert(stl_map_two.begin(), stl_map_two.end());
		stop_stl();
		start_ft();
		ft_map_one.insert(ft_map_two.begin(), ft_map_two.end());
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {754, -985, 58, 999, 5};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map_one;\n";
		fs << "ft::map<int, std::string> ft_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "	ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "	ft_map_two.insert(ft::make_pair(range_int[i] + 266, range_str[i] + \"_two\"));\n";
		fs << "}\n";
		fs << "Sending output...\n";
		fs << "ft_map_one.insert(ft_map_two.begin(), ft_map_two.end());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {754, -985, 58, 999, 5};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map_one;\n";
		fs << "std::map<int, std::string> stl_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "	stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "	stl_map_two.insert(std::make_pair(range_int[i] + 266, range_str[i] + \"_two\"));\n";
		fs << "}\n";
		fs << "Sending output...\n";
		fs << "stl_map_one.insert(stl_map_two.begin(), stl_map_two.end());\n";
		printMapAttributes(fs, stl_map_one, ft_map_one);
		printMapAttributes(fs, stl_map_two, ft_map_two);
		std::cout << std::setw(30) << std::left << "Insert range: " << std::setw(0) << ((printMapAttributes(fs, stl_map_one, ft_map_one) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();

	}

	/* Erase single */
	{
		const int range_int[] = {-9, -84, -77, 24, 56};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		stl_map.erase(stl_map.begin());
		stop_stl();
		start_ft();
		ft_map.erase(ft_map.begin());
		stop_ft();

		fs << "\nERASE SINGLE\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-9, -84, -77, 24, 56};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft_map.erase(ft_map.begin());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-9, -84, -77, 24, 56};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "stl_map.erase(stl_map.begin());\n";
		std::cout << std::setw(30) << std::left << "Erase single: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Erase key */
	{
		const int range_int[] = {-1452, -3651, -98, -84, -899};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		printMapAttributes(fs, stl_map, ft_map);
		start_stl();
		stl_map.erase(97598);
		stop_stl();
		start_ft();
		ft_map.erase(97598);
		stop_ft();

		fs << "\nERASE KEY\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-1452, -3651, -98, -84, -899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "ft_map.erase(-98);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-1452, -3651, -98, -84, -899};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "stl_map.erase(-98);\n";
		std::cout << std::setw(30) << std::left << "Erase key: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Erase range */
	{
        const int range_int[] = {-854, -1, -965, -9, -755};
        const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

        for (int i = 0; i < 1000; i++)
        {
            stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
            ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
        }

		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
        printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string>::iterator stl_it_beg = stl_map.begin();
		ft::map<int, std::string>::iterator ft_it_beg = ft_map.begin();
		std::map<int, std::string>::iterator stl_it_end = stl_map.end();
		ft::map<int, std::string>::iterator ft_it_end = ft_map.end();

		for (int i = 0; i < 2; i++)
		{
			stl_it_beg++;
			ft_it_beg++;
		}
		stl_it_end--;
		ft_it_end--;

		start_stl();
        stl_map.erase(stl_it_beg, stl_it_end);
        stop_stl();
		start_ft();
		ft_map.erase(ft_it_beg, ft_it_end);
		stop_ft();

		fs << "\nERASE RANGE\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "const int range_int[] = {-854, -1, -965, -9, -755};\n";
        fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
        fs << "for (int i = 0; i < 1000; i++)\n";
        fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it_beg = ft_map.begin();\n";
		fs << "ft::map<int, std::string>::iterator ft_it_end = ft_map.end();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "	ft_it_beg++;\n";
		fs << "ft_it_end--;\n";
        fs << "ft_map.erase(ft_it_beg, ft_it_end);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
        fs << "const int range_int[] = {-854, -1, -965, -9, -755};\n";
        fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
        fs << "for (int i = 0; i < 1000; i++)\n";
        fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "std::map<int, std::string>::iterator stl_it_beg = stl_map.begin();\n";
		fs << "std::map<int, std::string>::iterator stl_it_end = stl_map.end();\n";
		fs << "for (int i = 0; i < 2; i++)\n";
		fs << "	stl_it_beg++;\n";
		fs << "stl_it_end--;\n";
        fs << "stl_map.erase(stl_it_beg, stl_it_end);\n";
        std::cout << std::setw(30) << std::left << "Erase range: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Swap */
	{
		const int range_int[] = {489, 851, 32, -98, 8};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map_one;
		ft::map<int, std::string> ft_map_one;
		std::map<int, std::string> stl_map_two;
		ft::map<int, std::string> ft_map_two;

		for (int i = 0; i < 5; i++)
		{
			stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));
			stl_map_two.insert(std::make_pair(range_int[i] + 120, range_str[i]));
			ft_map_two.insert(ft::make_pair(range_int[i] + 120, range_str[i]));
		}

		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		printMapAttributes(fs, stl_map_one, ft_map_one);
		printMapAttributes(fs, stl_map_two, ft_map_two);

		start_stl();
		stl_map_one.swap(stl_map_two);
		stop_stl();
		start_ft();
		ft_map_one.swap(ft_map_two);
		stop_ft();

		fs << "\nSWAP\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {489, 851, 32, -98, 8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map_one;\n";
		fs << "ft::map<int, std::string> ft_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "		ft_map_one.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "		ft_map_two.insert(ft::make_pair(range_int[i] + 120, range_str[i]));\n";
		fs << "}\n";
		fs << "Sending Output...\n";
		fs << "ft_map_one.swap(ft_map_two);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {489, 851, 32, -98, 8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map_one;\n";
		fs << "std::map<int, std::string> stl_map_two;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "{\n";
		fs << "		stl_map_one.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "		stl_map_two.insert(std::make_pair(range_int[i] + 120, range_str[i]));\n";
		fs << "}\n";
		fs << "Sending Output...\n";
		fs << "stl_map_one.swap(stl_map_two);\n";
		std::cout << std::setw(30) << std::left << "Swap one: " << std::setw(0) << ((printMapAttributes(fs, stl_map_one, ft_map_one) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl;
		std::cout << std::setw(30) << std::left << "Swap two: " << std::setw(0) << ((printMapAttributes(fs, stl_map_two, ft_map_two) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Clear */
	{
		const int range_int[] = {-148, -9874, -987, -52, -96};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		printMapAttributes(fs, stl_map, ft_map);

		start_stl();
		stl_map.clear();
		stop_stl();
		start_ft();
		ft_map.clear();
		stop_ft();

		fs << "\nCLEAR\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-148, -9874, -987, -52, -96};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "ft_map.clear()\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-148, -9874, -987, -52, -96};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "stl_map.clear()\n";
		std::cout << std::setw(30) << std::left << "Clear: " << std::setw(0) << ((printMapAttributes(fs, stl_map, ft_map) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << std::endl;
	std::cout << YELLOW"Operations : \n" << NRM;
	fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Find exist */
	{
		const int range_int[] = {-954, -12, -965, -42, -1000};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);


		start_stl();
		std::map<int, std::string>::iterator stl_it = stl_map.find(42);
		stop_stl();
		start_ft();
		ft::map<int, std::string>::iterator ft_it = ft_map.find(42);
		stop_ft();
		printMapAttributes(fs, stl_map, ft_map);


		fs << "\nFIND\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-954, -12, -965, -42, -1000};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.find(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-954, -12, -965, -42, -1000};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i, range_str[i % 5]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.find(42);\n";
		std::cout << std::setw(30) << std::left << "Find: " << std::setw(0) << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]";
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Find not exist*/
	{
		const int range_int[] = {14, -985, 578, -23, -47};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : (i * 2) + 1, range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : (i * 2) + 1, range_str[i % 5]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		std::map<int, std::string>::iterator stl_it = stl_map.find(42);
		stop_stl();
		start_ft();
		ft::map<int, std::string>::iterator ft_it = ft_map.find(42);
		stop_ft();
		printMapAttributes(fs, stl_map, ft_map);

		fs << "\nFIND NOT EXISTS\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {14, -985, 578, -23, -47};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : (i * 2) + 1, range_str[i % 5]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.find(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {14, -985, 578, -23, -47};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : (i * 2) + 1, range_str[i % 5]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.find(42);\n";
		std::cout << std::setw(30) << std::left << "Find not exists: " << std::setw(0) << ((printBoolResult(fs, (stl_it == stl_map.end()), (ft_it == ft_map.end())) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const it Find */
	{
		const int range_int[] = {842, -965, 99, 52, 65};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);

		std::map<int, std::string>::const_iterator stl_it = stl_map.find(99);
		ft::map<int, std::string>::const_iterator ft_it = ft_map.find(99);

		printMapAttributes(fs, stl_map, ft_map);


		fs << "\nFIND CONST\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, -965, 99, 52, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.find(99);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, -965, 99, 52, 65};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.find(99);\n";
		std::cout << std::setw(30) << std::left << "Find const: " << std::setw(0) << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Count */
	{
		const int range_int[] = {842, 654, 95, -98, -8};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < 5; i++)
		{
			stl_map.insert(std::make_pair(range_int[i], range_str[i]));
			ft_map.insert(ft::make_pair(range_int[i], range_str[i]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);

		printMapAttributes(fs, stl_map, ft_map);


		fs << "\nCOUNT \nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 654, 95, -98, -8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "Search for -98 & 42\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {842, 654, 95, -98, -8};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "Search for -98 & 42\n";
		std::cout << std::setw(30) << std::left << "Count: " << std::setw(0) << "[";
		std::cout << ((printBoolResult(fs, (stl_map.count(-98) > 0), (ft_map.count(-98) > 0)) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printBoolResult(fs, (stl_map.count(42) > 0), (ft_map.count(42) > 0)) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Lower bound */
	{
		const int range_int[] = {-351, -999, -5, -76, -61};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);

		printMapAttributes(fs, stl_map, ft_map);

		start_stl();
		std::map<int, std::string>::iterator stl_it = stl_map.lower_bound(-76);
		stop_stl();
		start_ft();
		ft::map<int, std::string>::iterator ft_it = ft_map.lower_bound(-76);
		stop_ft();

		fs << "\nLOWER BOUND\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-351, -999, -5, -76, -61};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.lower_bound(-76);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-351, -999, -5, -76, -61};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.lower_bound(-76);\n";
		std::cout << std::setw(30) << std::left << "Lower bound: " << std::setw(0) << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]";
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const it Lower bound */
	{
		const int range_int[] = {-351, -999, -5, -76, -61};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
			  ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);

		printMapAttributes(fs, stl_map, ft_map);

		std::map<int, std::string>::iterator stl_it = stl_map.lower_bound(80);
		ft::map<int, std::string>::iterator ft_it = ft_map.lower_bound(80);


		fs << "\nLOWER BOUND CONST\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {554, 62, 345, 98, -77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(range_int[i], range_str[i]));\n";
		fs << "ft::map<int, std::string>::const_iterator ft_it = ft_map.lower_bound(80);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {554, 62, 345, 98, -77};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(range_int[i], range_str[i]));\n";
		fs << "std::map<int, std::string>::const_iterator stl_it = stl_map.lower_bound(80);\n";
		std::cout << std::setw(30) << std::left << "Lower bound const: " << std::setw(0) << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]\n\n";
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Upper bound */
	{
		const int range_int[] = {-351, -999, -5, -76, -61};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);

		printMapAttributes(fs, stl_map, ft_map);

		start_stl();
		std::map<int, std::string>::iterator stl_it = stl_map.upper_bound(950);
		stop_stl();
		start_ft();
		ft::map<int, std::string>::iterator ft_it = ft_map.upper_bound(950);
		stop_ft();

		fs << "\nUPPER BOUND\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-351, -999, -5, -76, -61};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));\n";
		fs << "ft::map<int, std::string>::iterator ft_it = ft_map.upper_bound(950);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {45, -84, 957, 966, 3};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < 5; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));\n";
		fs << "std::map<int, std::string>::iterator stl_it = stl_map.upper_bound(950);\n";
		std::cout << std::setw(30) << std::left << "Upper bound: " << std::setw(0) << "[";
		std::cout << ((printSingleValue(fs, (*stl_it).first, (*ft_it).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*stl_it).second, (*ft_it).second) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]";
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Equal range */
	{
		const int range_int[] = {-351, -999, -5, -76, -61};
		const std::string range_str[] = {"One", "Two", "Three", "Four", "Five"};

		std::map<int, std::string> stl_map;
		ft::map<int, std::string> ft_map;

		for (int i = 0; i < SIZE; i++)
		{
			stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
			ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));
		}

		fs.open("./tester/maps_output/operations", std::fstream::in | std::fstream::out | std::fstream::app);

		printMapAttributes(fs, stl_map, ft_map);

		start_stl();
		stl_map.equal_range(1989);
		stop_stl();
		start_ft();
		ft_map.equal_range(1989);
		stop_ft();

		fs << "\nEQUAL RANGE (look for 1989)\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-741, 520, 65, -84, -1};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "ft::map<int, std::string> ft_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    ft_map.insert(ft::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "const int range_int[] = {-741, 520, 65, -84, -1};\n";
		fs << "const std::string range_str[] = {\"One\", \"Two\", \"Three\", \"Four\", \"Five\"};\n";
		fs << "std::map<int, std::string> stl_map;\n";
		fs << "for (int i = 0; i < SIZE; i++)\n";
		fs << "    stl_map.insert(std::make_pair(i < 5 ? range_int[i] : i * (i % 50), range_str[i % 5]));\n";
		std::cout << std::setw(30) << std::left << "Equal range: " << std::setw(0) << "[";
		std::cout << ((printSingleValue(fs, (*(stl_map.equal_range(1989).first)).first, (*(ft_map.equal_range(1989).first)).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << ((printSingleValue(fs, (*(stl_map.equal_range(1989).second)).first, (*(ft_map.equal_range(1989).second)).first) == true) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		std::cout << "]";
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
}
