# include <vector>

# include "vector.hpp"
// # include "../containers/random_access_iterator.hpp"
# include "tester.hpp"

template <class T>
std::string equalContent(
	const std::vector<T> & stl_vector,
	const ft::vector<T> & ft_vector
)
{
	typename ft::vector<T>::const_iterator ft_it;
	typename std::vector<T>::const_iterator stl_it;
	if (ft_vector.size() != stl_vector.size())
		return ("✘");
	stl_it = stl_vector.begin();
	for(ft_it = ft_vector.begin(); ft_it != ft_vector.end(); ft_it++)
	{
		if (*ft_it != *stl_it)
			return ("✘");
		stl_it++;
	}
	return ("✔");
}

template <class T>
bool printVectorAttributes(
	std::fstream& fs,
	std::vector<T>& stl_vector,
	ft::vector<T>& ft_vector
)
{
	/* STL Values */
	std::string stl_empty = ((stl_vector.empty() == 1) ? "true" : "false");
	size_t stl_size = stl_vector.size();
	size_t stl_max_size = stl_vector.max_size();
	size_t stl_capacity = stl_vector.capacity();

	/* FT Values */
	std::string ft_empty = ((ft_vector.empty() == 1) ? "true" : "false");
	size_t ft_size = ft_vector.size();
	size_t ft_max_size = ft_vector.max_size();
	size_t ft_capacity = ft_vector.capacity();

	/* FT Result compare values */
	bool empty = equalbool(ft_empty, stl_empty);
	bool size = equalbool(ft_size, stl_size);
	bool max_size = equalbool(ft_max_size, stl_max_size);
	bool capacity = equalbool(ft_capacity, stl_capacity);
	std::string content = equalContent(stl_vector, ft_vector);

	fs << "\n══════════════════════════════════════════════════════════════\n";
	fs << "Vectors attributes : \n";
	fs << "STL : \n";
	fs << "Empty       : " << stl_empty  << std::endl;
	fs << "Size        : " << stl_size  << std::endl;
	fs << "Max size    : " << stl_max_size  << std::endl;
	fs << "Capacity    : " << stl_capacity  << std::endl;
	fs << "Content     : [";
	if (stl_vector.size() < 50)
	{

		typename std::vector<T>::const_iterator stl_it;
		for (stl_it = stl_vector.begin();  stl_it != stl_vector.end(); stl_it++)
		{
			fs << *stl_it;
			if (stl_it + 1 != stl_vector.end())
				fs << ", ";
		}
		fs << "]\n";

	}
	else
		fs << "...]\n";
	fs << std::endl;

	fs << "FT : \n";
	fs << "Empty    [" << equal(ft_empty, stl_empty) << "]: " << ft_empty  << std::endl;
	fs << "Size     [" << equal(ft_size, stl_size) << "]: " << ft_size  << std::endl;
	fs << "Max size [" << equal(ft_max_size, stl_max_size) << "]: " << ft_max_size  << std::endl;
	fs << "Capacity [" << equal(ft_capacity, stl_capacity) << "]: " << ft_capacity  << std::endl;
	fs << "Content  [" << content << "]: [";
	if (ft_vector.size() < 50)
	{

		typename ft::vector<T>::const_iterator ft_it;
		for(ft_it = ft_vector.begin(); ft_it != ft_vector.end(); ft_it++)
		{
			fs << *ft_it;
			if (ft_it + 1 != ft_vector.end())
				fs << ", ";
		}
		fs << "]\n";
	}
	else
		fs << "...]\n";

	fs << "══════════════════════════════════════════════════════════════\n\n\n";

	/* Error case */
	if (!empty || !max_size || !size || !capacity || content == "✘")
		return (false);
	return (true);
}

void test_vector()
{
	std::cout << UNDERLINE << BLUE << "VECTORS :\n" << NORMAL ;

	mkdir("./tester/vectors_output", 0777);

	std::fstream fs;

	/* Constructors */
	std::cout << YELLOW"Constructors : \n" << NRM;
	fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Default constructor */
	{
		start_stl();
		std::vector<int> stl_default_vector;
		stop_stl();
		start_ft();
		ft::vector<int> ft_default_vector;
		stop_ft();
		fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_default_vector;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_default_vector;\n";
		std::cout << std::setw(30) << std::left << "Default Costructor: " << std::setw(0) << (printVectorAttributes(fs, stl_default_vector, ft_default_vector) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Default constructor pointer */
	{
		start_stl();
		std::vector<int> *stl_pointer_default_vector = new std::vector<int>();
		stop_stl();
		start_ft();
		ft::vector<int> *ft_pointer_default_vector = new ft::vector<int>();
		stop_ft();
		fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> *ft_pointer_default_vector = new ft::vector<int>;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> *stl_pointer_default_vector = new std::vector<int>;\n";
		std::cout << std::setw(30) << std::left << "Default constructor pointer: " << std::setw(0) << (printVectorAttributes(
                fs, *stl_pointer_default_vector, *ft_pointer_default_vector) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();

		delete stl_pointer_default_vector;
		delete ft_pointer_default_vector;
	}

	/* Fill constructor */
	{
		start_stl();
		std::vector<int> stl_fill_vector(0);
		stop_stl();
		start_ft();
		ft::vector<int> ft_fill_vector(0);
		stop_ft();

		fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_fill_vector(0);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_fill_vector(0);\n";
		std::cout << std::setw(30) << std::left << "Fill constructor: " << std::setw(0) << (printVectorAttributes(fs, stl_fill_vector, ft_fill_vector) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Fill constructor sized */
	{
		start_stl();
		std::vector<int> stl_fill_vector_sized(19);
		stop_stl();
		start_ft();
		ft::vector<int> ft_fill_vector_sized(19);
		stop_ft();
		fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_fill_vector_sized(19);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_fill_vector_sized(19);\n";
		std::cout << std::setw(30) << std::left << "Fill constructor sized: " << std::setw(0) << (printVectorAttributes(fs, stl_fill_vector_sized, ft_fill_vector_sized) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Fill constructor sized & valued */
	{
		start_stl();
		std::vector<int> stl_fill_vector_sized(19, 42);
		stop_stl();
		start_ft();
		ft::vector<int> ft_fill_vector_sized(19, 42);
		stop_ft();

		fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_fill_vector_sized(19, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_fill_vector_sized(19, 42);\n";
		std::cout << std::setw(30) << std::left << "Fill constr sized & valued: " << std::setw(0) << (printVectorAttributes(fs, stl_fill_vector_sized, ft_fill_vector_sized) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Range constructor */
	{
		int range_array[] = { 45, 87846, 12, 965, 5 };
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator(range.begin());
		ft::vector<int>::iterator ft_iterator(&(range_array[0]));

		fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
		stop_stl();
		start_ft();
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 45, 87846, 12, 965, 5 };\n";
		fs << "int range_array__[] = { 45, 87846, 12, 965, 5 };\n";
		fs << "int range_array__[] = { 45, 87846, 12, 965, 5 };\n";
		fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 45, 87846, 12, 965, 5 };\n";
		fs << "int range_array__[] = { 45, 87846, 12, 965, 5 };\n";
		fs << "int range_array__[] = { 45, 87846, 12, 965, 5 };\n";
		fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		std::cout << std::setw(30) << std::left << "Range constructor: " << std::setw(0) << (printVectorAttributes(fs, stl_range_vector, ft_range_vector) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Copy constructor */
	{
		int range_array[] = { -89, 561, 874, 7777 , 987, -6 };
        std::vector<int> range;
        for (int i = 0; i < 6; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator(range.begin());
		ft::vector<int>::iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 6);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 6);

		fs.open("./tester/vectors_output/constructor", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		std::vector<int> stl_copy_vector(stl_range_vector);
		stop_stl();
		start_ft();
		ft::vector<int> ft_copy_vector(ft_range_vector);
		stop_ft();


		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { -89, 561, 874, 7777 , 987, -6 };\n";
		fs << "int range_array__[] = { -89, 561, 874, 7777 , 987, -6 };\n";
		fs << "int range_array__[] = { -89, 561, 874, 7777 , 987, -6 };\n";
		fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 6);\n";
		fs << "ft::vector<int> ft_copy_vector(ft_range_vector);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { -89, 561, 874, 7777 , 987, -6 };\n";
		fs << "int range_array__[] = { -89, 561, 874, 7777 , 987, -6 };\n";
		fs << "int range_array__[] = { -89, 561, 874, 7777 , 987, -6 };\n";
		fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 6);\n";
		fs << "std::vector<int> stl_copy_vector(stl_range_vector);\n";
		std::cout << std::setw(30) << std::left << "Copy constructor: " << std::setw(0) << (printVectorAttributes(fs, stl_copy_vector, ft_copy_vector) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << YELLOW"Assign : \n" << NRM;

	/* Assign operator */
	{
		std::vector<int> stl_range_vector(1000000, 10);
		ft::vector<int> ft_range_vector(1000000, 10);

		fs.open("./tester/vectors_output/assign", std::fstream::in | std::fstream::out | std::fstream::trunc);
		start_stl();
		std::vector<int> stl_assign_vector = stl_range_vector;
		stop_stl();
		start_ft();
		ft::vector<int> ft_assign_vector = ft_range_vector;
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 74, 569, -8822, 8515, 5 };\n";
		fs << "int range_array__[] = { 74, 569, -8822, 8515, 5 };\n";
		fs << "int range_array__[] = { 74, 569, -8822, 8515, 5 };\n";
		fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "ft::vector<int> ft_assign_vector = ft_range_vector;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 74, 569, -8822, 8515, 5 };\n";
		fs << "int range_array__[] = { 74, 569, -8822, 8515, 5 };\n";
		fs << "int range_array__[] = { 74, 569, -8822, 8515, 5 };\n";
		fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		fs << "std::vector<int> stl_assign_vector = stl_range_vector;\n";
		std::cout << std::setw(30) << std::left << "Assign operator: " << std::setw(0) << (printVectorAttributes(fs, stl_assign_vector, ft_assign_vector) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << YELLOW"Iterator : \n" << NRM;
	fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Iterator begin() */
	{
		int range_array[] = { 87, 92, -5, 8984, 96 };
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator(range.begin());
		ft::vector<int>::iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);
		start_stl();
		int from_stl = *(stl_range_vector.begin());
		stop_stl();
		start_ft();
		int from_ft = *(ft_range_vector.begin());
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "int from_ft = *(ft_range_vector.begin());\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		fs << "int from_stl = *(stl_range_vector.begin());\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Iterator begin(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const iterator begin() */
	{
		int range_array[] = { 87, 92, -5, 8984, 96 };
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::const_iterator stl_iterator(range.begin());
		ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);

		std::vector<int>::const_iterator stl_const_it = stl_range_vector.begin();
		ft::vector<int>::const_iterator ft_const_it = ft_range_vector.begin();
		start_stl();
		const int from_stl = *(stl_const_it);
		stop_stl();
		start_ft();
		const int from_ft = *(ft_const_it);
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "ft::vector<int>::const_iterator ft_const_it = ft_range_vector.begin();\n";
		fs << "int from_ft = *(ft_const_it);\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "int range_array__[] = { 87, 92, -5, 8984, 96 };\n";
		fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		fs << "std::vector<int>::const_iterator stl_const_it = stl_range_vector.begin();\n";
		fs << "int from_stl = *(stl_const_it);\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Const iterator begin(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Iterator end() */
	{
		int range_array[] = { 48, 967, 52, -45, -9, 956551, 44};
        std::vector<int> range;
        for (int i = 0; i < 7; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator(range.begin());
		ft::vector<int>::iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);
		start_stl();
		int from_stl = *(stl_range_vector.end() - 1);
		stop_stl();
		start_ft();
		int from_ft = *(ft_range_vector.end() - 1);
		stop_ft();

		fs << "\nCode executed:\n";

		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
		fs << "int range_array__[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
		fs << "int range_array__[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
		fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);\n";
		fs << "int from_ft = *(ft_range_vector.end() - 1);\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
		fs << "int range_array__[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
		fs << "int range_array__[] = { 48, 967, 52, -45, -9, 956551, 44};\n";
		fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);\n";
		fs << "int from_stl = *(stl_range_vector.end() - 1);\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Iterator end(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const iterator end() */
	{
		int range_array[] = { 95, 89, -6121, 48, 5 };
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::const_iterator stl_iterator(range.begin());
		ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);

		std::vector<int>::const_iterator stl_const_it = stl_range_vector.end() - 1;
		ft::vector<int>::const_iterator ft_const_it = ft_range_vector.end() - 1;
		start_stl();
		const int from_stl = *(stl_const_it);
		stop_stl();
		start_ft();
		const int from_ft = *(ft_const_it);
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 95, 89, -6121, 48, 5 };\n";
		fs << "int range_array__[] = { 95, 89, -6121, 48, 5 };\n";
		fs << "int range_array__[] = { 95, 89, -6121, 48, 5 };\n";
		fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "std::vector<int>::const_iterator stl_const_it = stl_range_vector.end() - 1;\n";
		fs << "int from_ft = *(ft_const_it);\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 95, 89, -6121, 48, 5 };\n";
		fs << "int range_array__[] = { 95, 89, -6121, 48, 5 };\n";
		fs << "int range_array__[] = { 95, 89, -6121, 48, 5 };\n";
		fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		fs << "ft::vector<int>::const_iterator ft_const_it = ft_range_vector.end() - 1;\n";
		fs << "int from_stl = *(stl_const_it);\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Const iterator end(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Iterator rbegin() */
	{
		int range_array[] = {250, -1200, -98657, 2, 34};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator(range.begin());
		ft::vector<int>::iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);

		start_stl();
		int from_stl = *(stl_range_vector.rbegin());
		stop_stl();
		start_ft();
		int from_ft = *(ft_range_vector.rbegin());
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {250, -1200, -98657, 2, 34};\n";
		fs << "int range_array__[] = {250, -1200, -98657, 2, 34};\n";
		fs << "int range_array__[] = {250, -1200, -98657, 2, 34};\n";
		fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "int from_ft = *(ft_range_vector.rbegin());\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {250, -1200, -98657, 2, 34};\n";
		fs << "int range_array__[] = {250, -1200, -98657, 2, 34};\n";
		fs << "int range_array__[] = {250, -1200, -98657, 2, 34};\n";
		fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		fs << "int from_stl = *(stl_range_vector.rbegin());\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Iterator rbegin(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const iterator rbegin() */
	{
		int range_array[] = { 958, -561, 54, 789, -8};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::const_iterator stl_iterator(range.begin());
		ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);

		std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rbegin();
		ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rbegin();
		start_stl();
		const int from_stl = *(stl_const_it);
		stop_stl();
		start_ft();
		const int from_ft = *(ft_const_it);
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 958, -561, 54, 789, -8};\n";
		fs << "int range_array__[] = { 958, -561, 54, 789, -8};\n";
		fs << "int range_array__[] = { 958, -561, 54, 789, -8};\n";
		fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rbegin();\n";
		fs << "int from_ft = *(ft_const_it);\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 958, -561, 54, 789, -8};\n";
		fs << "int range_array__[] = { 958, -561, 54, 789, -8};\n";
		fs << "int range_array__[] = { 958, -561, 54, 789, -8};\n";
		fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		fs << "std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rbegin();\n";
		fs << "int from_stl = *(stl_const_it);\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Const iterator rbegin(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

		/* Iterator rend() */
	{
		int range_array[] = {78, -951, 562, 8, 745, 51236, 6987};
        std::vector<int> range;
        for (int i = 0; i < 7; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator(range.begin());
		ft::vector<int>::iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);
		start_stl();
		int from_stl = *(stl_range_vector.rend() - 1);
		stop_stl();
		start_ft();
		int from_ft = *(ft_range_vector.rend() - 1);
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
		fs << "int range_array__[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
		fs << "int range_array__[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
		fs << "ft::vector<int>::iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 7);\n";
		fs << "int from_ft = *(ft_range_vector.rend() - 1);\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
		fs << "int range_array__[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
		fs << "int range_array__[] = {78, -951, 562, 8, 745, 51236, 6987};\n";
		fs << "std::vector<int>::iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 7);\n";
		fs << "int from_stl = *(stl_range_vector.rend() - 1);\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Iterator rend(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		evaluate_speed(fs);
		print_speed();
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const iterator rend() */
	{
		int range_array[] = { 8, -5615, 412, 89, 475};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::const_iterator stl_iterator(range.begin());
		ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));

		std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);
		ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);

		fs.open("./tester/vectors_output/iterator", std::fstream::in | std::fstream::out | std::fstream::app);

		std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rend() - 1;
		ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rend() - 1;
		start_stl();
		const int from_stl = *(stl_const_it);
		stop_stl();
		start_ft();
		const int from_ft = *(ft_const_it);
		stop_ft();

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "ft::vector<int>::const_iterator ft_iterator(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_range_vector(ft_iterator, ft_iterator + 5);\n";
		fs << "std::vector<int>::const_reverse_iterator stl_const_it = stl_range_vector.rend() - 1;\n";
		fs << "int from_ft = *(ft_const_it);\n";
		fs << "    ^^^^^^^\n";
		fs << "    Compared value";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "std::vector<int>::const_iterator stl_iterator(&(range_array[0]));\n";
		fs << "std::vector<int> stl_range_vector(stl_iterator, stl_iterator + 5);\n";
		fs << "ft::vector<int>::const_reverse_iterator ft_const_it = ft_range_vector.rend() - 1;\n";
		fs << "int from_stl = *(stl_const_it);\n";
		fs << "    ^^^^^^^^\n";
		fs << "    Compared value";
		std::cout << std::setw(30) << std::left << "Const iterator rend(): " << (printSingleValue(fs, from_stl, from_ft) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		evaluate_speed(fs);
		print_speed();
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << YELLOW"Capacity : \n" << NRM;


	fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Size small */
	{
		std::vector<int> stl_filled(20);
		ft::vector<int> ft_filled(20);

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_filled(20);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_filled(20);\n";
		std::cout << std::setw(30) << std::left << "Size small: " << std::setw(0) << (printVectorAttributes(fs, stl_filled, ft_filled) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Size big */
	{
		std::vector<int> stl_filled(100000);
		ft::vector<int> ft_filled(100000);

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_filled(1000000);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_filled(1000000);\n";
		std::cout << std::setw(30) << std::left << "Size big: " << std::setw(0) << (printVectorAttributes(fs, stl_filled, ft_filled) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Maximum size */
	{
		std::vector<int> stl_base;
		ft::vector<int> ft_base;

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base;\n";
		std::cout << std::setw(30) << std::left << "Maximum size: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Resize extension */
	{
		std::vector<int> stl_base(40);
		ft::vector<int> ft_base(40);
		start_stl();
		stl_base.resize(85);
		stop_stl();
		start_ft();
		ft_base.resize(85);
		stop_ft();

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base(40);\n";
		fs << "ft_base.resize(85);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base(40);\n";
		fs << "stl_base.resize(85);\n";
		std::cout << std::setw(30) << std::left << "Resize extension: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Resize reduction */
	{
		std::vector<int> stl_base(40);
		ft::vector<int> ft_base(40);
		start_stl();
		stl_base.resize(3);
		stop_stl();
		start_ft();
		ft_base.resize(3);
		stop_ft();

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base(40);\n";
		fs << "ft_base.resize(3);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base(40);\n";
		fs << "stl_base.resize(3);\n";
		std::cout << std::setw(30) << std::left << "Resize reduction: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Capacity short */
	{
		std::vector<int> stl_base(40);
		ft::vector<int> ft_base(40);
		start_stl();
		stl_base.push_back(42);
		stl_base.push_back(69);
		stop_stl();
		start_ft();
		ft_base.push_back(42);
		ft_base.push_back(69);
		stop_ft();

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base(40);\n";
		fs << "ft_base.push_back(42);\n";
		fs << "ft_base.push_back(69);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base(40);\n";
		fs << "stl_base.push_back(42);\n";
		fs << "stl_base.push_back(69);\n";
		std::cout << std::setw(30) << std::left << "Capacity short: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Capacity big */
	{
		std::vector<int> stl_base(40000);
		ft::vector<int> ft_base(40000);

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base(40000);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base(40000);\n";
		std::cout << std::setw(30) << std::left << "Capacity big: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Empty true */
	{
		std::vector<int> stl_base;
		ft::vector<int> ft_base;

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base;\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base;\n";
		std::cout << std::setw(30) << std::left << "Empty true: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Empty false */
	{
		std::vector<int> stl_base(5);
		ft::vector<int> ft_base(5);

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base(5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base(5);\n";
		std::cout << std::setw(30) << std::left << "Empty false: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Empty after resize */
	{
		std::vector<int> stl_base(5);
		ft::vector<int> ft_base(5);

		stl_base.resize(0);
		ft_base.resize(0);

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base(5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base(5);\n";
		fs << "stl_base.resize(0);\n";
		std::cout << std::setw(30) << std::left << "Empty after resize: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Reserve normal */
	{
		std::vector<int> stl_base;
		ft::vector<int> ft_base;
		start_stl();
		stl_base.reserve(100);
		stl_base.push_back(42);
		stop_stl();
		start_ft();
		ft_base.reserve(100);
		ft_base.push_back(42);
		stop_ft();

		fs.open("./tester/vectors_output/capacity", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_base;\n";
		fs << "ft_base.reserve(100);\n";
		fs << "ft_base.push_back(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_base;\n";
		fs << "stl_base.reserve(100);\n";
		fs << "stl_base.push_back(42);\n";
		std::cout << std::setw(30) << std::left << "Reserve normal: " << std::setw(0) << (printVectorAttributes(fs, stl_base, ft_base) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << YELLOW"Element access : \n" << NRM;
	fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Operator [] */
	{
		int range_array[] = { 8, -5615, 412, 89, 475};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);

		start_stl();
		stl_operator[1];
		stop_stl();
		start_ft();
		ft_operator[1];
		stop_ft();

		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "int range_array__[] = { 8, -5615, 412, 89, 475};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Operator []: " << (printSingleValue(fs, stl_operator[1], ft_operator[1]) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const Operator [] */
	{
		int range_array[] = {8, -98, 541, 53361, 9};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		const int stl_const = stl_operator[1];
		stop_stl();
		start_ft();
		const int ft_const = ft_operator[1];
		stop_ft();

		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {8, -98, 541, 53361, 9};\n";
		fs << "int range_array__[] = {8, -98, 541, 53361, 9};\n";
		fs << "int range_array__[] = {8, -98, 541, 53361, 9};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_operator(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "const int stl_const = stl_operator[1];\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {8, -98, 541, 53361, 9};\n";
		fs << "int range_array__[] = {8, -98, 541, 53361, 9};\n";
		fs << "int range_array__[] = {8, -98, 541, 53361, 9};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_operator(stl_iterator_beg, stl_iterator_beg + 5);\n";
		fs << "const int stl_const = stl_operator[1];\n";
		std::cout << std::setw(30) << std::left << "Const Operator []: " << (printSingleValue(fs, stl_const, ft_const) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Normal at() */
	{
		int range_array[] = {8, -986, -8, 66, 7};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		stl_at.at(3);
		stop_stl();
		start_ft();
		ft_at.at(3);
		stop_ft();
		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {8, -986, -8, 66, 7};\n";
		fs << "int range_array__[] = {8, -986, -8, 66, 7};\n";
		fs << "int range_array__[] = {8, -986, -8, 66, 7};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {8, -986, -8, 66, 7};\n";
		fs << "int range_array__[] = {8, -986, -8, 66, 7};\n";
		fs << "int range_array__[] = {8, -986, -8, 66, 7};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Normal at(): " << (printSingleValue(fs, stl_at.at(3), ft_at.at(3)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const at() */
	{
		int range_array[] = {845, -9, 47, 4, -825};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		const int stl_const = stl_at.at(4);
		stop_stl();
		start_ft();
		const int ft_const = ft_at.at(4);
		stop_ft();

		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {845, -9, 47, 4, -825};\n";
		fs << "int range_array__[] = {845, -9, 47, 4, -825};\n";
		fs << "int range_array__[] = {845, -9, 47, 4, -825};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_at(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "const int stl_const = stl_at.at(4);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {845, -9, 47, 4, -825};\n";
		fs << "int range_array__[] = {845, -9, 47, 4, -825};\n";
		fs << "int range_array__[] = {845, -9, 47, 4, -825};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_at(stl_iterator_beg, stl_iterator_beg + 5);\n";
		fs << "const int ft_const = ft_at.at(4);\n";
		std::cout << std::setw(30) << std::left << "Const at(): " << (printSingleValue(fs, stl_const, ft_const) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Normal front() */
	{
		int range_array[] = {2, 0, 982, -9, 87};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);

		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Normal front(): " << (printSingleValue(fs, stl_front.front(), ft_front.front()) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const front() */
	{
		int range_array[] = {5589, -97, -98, -63, 8};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		const int stl_const = stl_front.front();
		stop_stl();
		start_ft();
		const int ft_const = ft_front.front();
		stop_ft();

		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_front(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "const int ft_const = ft_front.front();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_front(stl_iterator_beg, stl_iterator_beg + 5);\n";
		fs << "const int stl_const = stl_front.front();\n";
		std::cout << std::setw(30) << std::left << "Const front(): " << (printSingleValue(fs, stl_const, ft_const) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Normal back() */
	{
		int range_array[] = {2, 0, 982, -9, 87};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);

		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "int range_array__[] = {2, 0, 982, -9, 87};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Normal back(): " << (printSingleValue(fs, stl_back.back(), ft_back.back()) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl;
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Const back() */
	{
		int range_array[] = {5589, -97, -98, -63, 8};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		const int stl_const = stl_back.back();
		stop_stl();
		start_ft();
		const int ft_const = ft_back.back();
		stop_ft();

		fs.open("./tester/vectors_output/access", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_back(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "const int ft_const = ft_back.back();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "int range_array__[] = {5589, -97, -98, -63, 8};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_back(stl_iterator_beg, stl_iterator_beg + 5);\n";
		fs << "const int stl_const = stl_back.back();\n";
		std::cout << std::setw(30) << std::left << "Const back(): " << (printSingleValue(fs, stl_const, ft_const) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << YELLOW"Modifiers : \n" << NRM;

	fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();
	/* Assign range */
	{
		int range_array[] = {84, 522, -654, -7623, 4};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_assign;
		ft::vector<int> ft_assign;
		start_stl();
		stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);
		stop_stl();
		 start_ft();
		ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {84, 522, -654, -7623, 4};\n";
		fs << "int range_array__[] = {84, 522, -654, -7623, 4};\n";
		fs << "int range_array__[] = {84, 522, -654, -7623, 4};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_assign;\n";
		fs << "ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {84, 522, -654, -7623, 4};\n";
		fs << "int range_array__[] = {84, 522, -654, -7623, 4};\n";
		fs << "int range_array__[] = {84, 522, -654, -7623, 4};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_assign;\n";
		fs << "stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Assign range: " << std::setw(0) << (printVectorAttributes(fs, stl_assign, ft_assign) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Assign range replace */
	{
		int range_array[] = {547, 98, -6, 0, 47};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_assign(42);
		ft::vector<int> ft_assign(42);
		start_stl();
		stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);
		stop_stl();
		start_ft();
		ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_assign;\n";
		fs << "ft_assign.assign(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_assign;\n";
		fs << "stl_assign.assign(stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Assign range replace: " << std::setw(0) << (printVectorAttributes(fs, stl_assign, ft_assign) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Assign fill */
	{
		std::vector<int> stl_assign_fill;
		ft::vector<int> ft_assign_fill;
		start_stl();
		stl_assign_fill.assign(87, 42);
		stop_stl();
		start_ft();
		ft_assign_fill.assign(87, 42);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_assign_fill;\n";
		fs << "ft_assign_fill.assign(87, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_assign_fill;\n";
		fs << "stl_assign_fill.assign(87, 42);\n";
		std::cout << std::setw(30) << std::left << "Assign fill: " << std::setw(0) << (printVectorAttributes(fs, stl_assign_fill, ft_assign_fill) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Assign fill Replace */
	{
		std::vector<int> stl_assign_fill(42);
		ft::vector<int> ft_assign_fill(42);

		start_stl();
		stl_assign_fill.assign(420, 14);
		stop_stl();
		start_ft();
		ft_assign_fill.assign(420, 14);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_assign_fill;\n";
		fs << "ft_assign_fill.assign(87, 42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_assign_fill;\n";
		fs << "stl_assign_fill.assign(87, 42);\n";
		std::cout << std::setw(30) << std::left << "Assign fill Replace: " << std::setw(0) << (printVectorAttributes(fs, stl_assign_fill, ft_assign_fill) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Push back empty */
	{
		std::vector<int> stl_pushback;
		ft::vector<int> ft_pushback;
		start_stl();
		stl_pushback.push_back(42);
		stop_stl();
		start_ft();
		ft_pushback.push_back(42);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_pushback;\n";
		fs << "ft_pushback.push_back(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_pushback;\n";
		fs << "stl_pushback.push_back(42);\n";
		std::cout << std::setw(30) << std::left << "Push back empty: " << std::setw(0) << (printVectorAttributes(fs, stl_pushback, ft_pushback) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Push back */
	{
		std::vector<int> stl_pushback(7);
		ft::vector<int> ft_pushback(7);
		start_stl();
		stl_pushback.push_back(42);
		stop_stl();
		start_ft();
		ft_pushback.push_back(42);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_pushback(7);\n";
		fs << "ft_pushback.push_back(42);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_pushback(7);\n";
		fs << "stl_pushback.push_back(42);\n";
		std::cout << std::setw(30) << std::left << "Push back: " << std::setw(0) << (printVectorAttributes(fs, stl_pushback, ft_pushback) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Pop back */
	{
		int range_array[] = {547, 98, -6, 0, 47};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_popback(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_popback(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		stl_popback.pop_back();
		stop_stl();
		start_ft();
		ft_popback.pop_back();
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "ft::vector<int> ft_popback(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "ft_popback.pop_back();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "int range_array__[] = {547, 98, -6, 0, 47};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "stl_popback.pop_back();\n";
		std::cout << std::setw(30) << std::left << "Pop back: " << std::setw(0) << (printVectorAttributes(fs, stl_popback, ft_popback) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Insert single element */
	{
		int range_array[] = {478, 87, -85, 44, 7};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_insert(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_insert(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		stl_insert.insert(stl_insert.begin() + 2, 9999);
		stop_stl();
		start_ft();
		ft_insert.insert(ft_insert.begin() + 2, 9999);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {478, 87, -85, 44, 7};\n";
		fs << "int range_array__[] = {478, 87, -85, 44, 7};\n";
		fs << "int range_array__[] = {478, 87, -85, 44, 7};\n";
		fs << "ft::vector<int> ft_insert(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "ft_insert.pop_back();\n";
		fs << "ft_insert.insert(ft_insert.begin() + 2, 9999);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_[] = {478, 87, -85, 44, 7};\n";
		fs << "int range_array__[] = {478, 87, -85, 44, 7};\n";
		fs << "int range_array__[] = {478, 87, -85, 44, 7};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "stl_insert.insert(stl_insert.begin() + 2, 9999);\n";
		std::cout << std::setw(30) << std::left << "Insert single element: " << std::setw(0) << (printVectorAttributes(fs, stl_insert, ft_insert) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Insert fill */
	{
		start_stl();
		std::vector<int> stl_insert(1000);
		stop_stl();
		start_ft();
		ft::vector<int> ft_insert(1000);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "ft::vector<int> ft_insert(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "ft_insert.insert(ft_insert.begin() + 2, 6, 4269);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "stl_insert.insert(stl_insert.begin() + 2, 6, 4269);\n";
		std::cout << std::setw(30) << std::left << "Insert fill: " << std::setw(0) << (printVectorAttributes(fs, stl_insert, ft_insert) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") ;
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Insert range */
	{
		int range_array[] = {47, 152, -325, 9, 14444};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_insert(4);
		ft::vector<int> ft_insert(4);
		start_stl();
		stl_insert.insert(stl_insert.end(), stl_iterator_beg, stl_iterator_beg + 5);
		stop_stl();
		start_ft();
		ft_insert.insert(ft_insert.end(), ft_iterator_beg, ft_iterator_beg + 5);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_insert(4);\n";
		fs << "ft_insert.insert(ft_insert.end(), ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_insert(4);\n";
		fs << "stl_insert.insert(stl_insert.end(), stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Insert range: " << std::setw(0) << (printVectorAttributes(fs, stl_insert, ft_insert) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Insert range large*/
	{
		int range_array[] = {47, 152, -325, 9, 14444};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_insert(100000, 1);
		ft::vector<int> ft_insert(100000, 1);
		start_stl();
		stl_insert.insert(stl_insert.begin() + 100, stl_iterator_beg, stl_iterator_beg + 5);
		stop_stl();
		start_ft();
		ft_insert.insert(ft_insert.begin() + 100, ft_iterator_beg, ft_iterator_beg + 5);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_insert(100000, 1);\n";
		fs << "ft_insert.insert(ft_insert.end(), ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_insert(100000, 1);\n";
		fs << "stl_insert.insert(stl_insert.end(), stl_iterator_beg, stl_iterator_beg + 5);\n";
		std::cout << std::setw(30) << std::left << "Insert range large: " << std::setw(0) << (printVectorAttributes(fs, stl_insert, ft_insert) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Erase single element */
	{
		int range_array[] = {47, 152, -325, 9, 14444};
        std::vector<int> range;
        for (int i = 0; i < 5; ++i)
            range.push_back(range_array[i]);

		std::vector<int>::iterator stl_iterator_beg(range.begin());
		ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));

		std::vector<int> stl_erase(stl_iterator_beg, stl_iterator_beg + 5);
		ft::vector<int> ft_erase(ft_iterator_beg, ft_iterator_beg + 5);
		start_stl();
		stl_erase.erase(stl_erase.begin() + 2);
		stop_stl();
		start_ft();
		ft_erase.erase(ft_erase.begin() + 2);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg(&(range_array[0]));\n";
		fs << "ft::vector<int> ft_erase(ft_iterator_beg, ft_iterator_beg + 5);\n";
		fs << "ft_erase.erase(ft_erase.begin());\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array[] = {47, 152, -325, 9, 14444};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg(&(range_array[0]));\n";
		fs << "std::vector<int> stl_erase(stl_iterator_beg, stl_iterator_beg + 5);\n";
		fs << "stl_erase.erase(stl_erase.begin());\n";
		std::cout << std::setw(30) << std::left << "Erase single element: " << std::setw(0) << (printVectorAttributes(fs, stl_erase, ft_erase) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Erase range */
	{
		std::vector<int> stl_erase(100000, 10);
		ft::vector<int> ft_erase(100000, 10);
		start_stl();
		stl_erase.erase(stl_erase.begin() + 1, stl_erase.begin() + 1000);
		stop_stl();
		start_ft();
		ft_erase.erase(ft_erase.begin() + 1, ft_erase.begin() + 1000);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_erase(100000, 10);\n";
		fs << "ft_erase.erase(ft_erase.begin() + 1, ft_erase.begin() + 1000);\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_erase(100000, 10);\n";
		fs << "stl_erase.erase(stl_erase.begin() + 1, stl_erase.begin() + 1000);\n";
		std::cout << std::setw(30) << std::left << "Erase range: " << std::setw(0) << (printVectorAttributes(fs, stl_erase, ft_erase) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Swap */
	{
		int range_array_one[] = {1458, -98, 745, 62, 9};
		int range_array_two[] = {478, 87, -15, 44, 7};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		start_stl();
		stl_swap_one.swap(stl_swap_two);
		stop_stl();
		start_ft();
		ft_swap_one.swap(ft_swap_two);
		stop_ft();

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
		fs << "int range_array_two[] = {478, 87, -15, 44, 7};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "Swap two: " << std::setw(0) << (printVectorAttributes(fs, stl_swap_two, ft_swap_two) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m")  << std::endl;
		fs << "ft_swap_one.swap(ft_swap_two);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
		fs << "int range_array_two[] = {478, 87, -15, 44, 7};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		fs << "stl_swap_one.swap(stl_swap_two);\n";
		std::cout << std::setw(30) << std::left << "Swap one: " << std::setw(0) << (printVectorAttributes(fs, stl_swap_one, ft_swap_one) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Clear */
	{
		std::vector<int> stl_clear(1000000, 42);
		ft::vector<int> ft_clear(1000000, 42);
		start_stl();
		stl_clear.clear();
		stop_stl();
		start_ft();
		ft_clear.clear();
		stop_ft();

		for (int i = 0; i < 100; ++i)
		{
			stl_clear.push_back(21);
			ft_clear.push_back(21);
		}

		fs.open("./tester/vectors_output/modifiers", std::fstream::in | std::fstream::out | std::fstream::app);
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "ft::vector<int> ft_clear(1000000, 42);\n";
		fs << "ft_clear.clear();\n";
		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "std::vector<int> stl_clear(1000000, 42);\n";
		fs << "stl_clear.clear();\n";
		fs << "for (int i = 0; i < 100; ++i)\n";
		fs << "{\n";
		fs << "	stl_clear.push_back(21);\n";
		fs << "	ft_clear.push_back(21);\n";
		fs << "}\n";
		std::cout << std::setw(30) << std::left << "Clear: " << std::setw(0) << (printVectorAttributes(fs, stl_clear, ft_clear) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
	std::cout << YELLOW"fi member function overloads : \n" << NRM;

	/* RL = Relation operator */
	fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::trunc);
	fs.close();

	/* RL '==' true */
	{
		int range_array_one[] = {1458, -98, 745, 62, 9};
		int range_array_two[] = {1458, -98, 745, 62, 9};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_equal_one, ft_equal_one);
		printVectorAttributes(fs, stl_equal_two, ft_equal_two);

		start_stl();
		if(stl_equal_one == stl_equal_two){}
		stop_stl();
		start_ft();
		if(ft_equal_one == ft_equal_two){}
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
		fs << "int range_array_two[] = {1458, -98, 745, 62, 9};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {1458, -98, 745, 62, 9};\n";
		fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '==' true: " << (printBoolResult(fs, (stl_equal_one == stl_equal_two), (ft_equal_one == ft_equal_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '==' false */
	{
		int range_array_one[] = {144, 335, 5, 0, -54};
		int range_array_two[] = {1458, -98, 745, 62, 9};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_equal_one, ft_equal_one);
		printVectorAttributes(fs, stl_equal_two, ft_equal_two);

		start_stl();
		if(stl_equal_one == stl_equal_two){};
		stop_stl();
		start_ft();
		if(ft_equal_one == ft_equal_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {1458, -98, 745, 62, 9};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_equal_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_equal_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_equal_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_equal_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '==' false: " << (printBoolResult(fs, (stl_equal_one == stl_equal_two), (ft_equal_one == ft_equal_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '!=' true */
	{
		int range_array_one[] = {144, 335, 5, 0, -54};
		int range_array_two[] = {1458, -98, 745, 62, 9};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one != stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one != ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {1458, -98, 745, 62, 9};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {1458, -98, 745, 62, 9};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '!=' true: " << (printBoolResult(fs, (stl_operator_one != stl_operator_two), (ft_operator_one != ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '!=' false */
	{
		int range_array_one[] = {144, 335, 5, 0, -54};
		int range_array_two[] = {144, 335, 5, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one != stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one != ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '!=' false: " << (printBoolResult(fs, (stl_operator_one != stl_operator_two), (ft_operator_one != ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '<' true */
	{
		int range_array_one[] = {144, 335, 1, -98, 5};
		int range_array_two[] = {144, 335, 5, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one < stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one < ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '<' true: " << (printBoolResult(fs, (stl_operator_one < stl_operator_two), (ft_operator_one < ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '<' false */
	{
		int range_array_one[] = {6780, 335, 1, -98, 5};
		int range_array_two[] = {144, 335, 5, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one < stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one < ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {6780, 335, 1, -98, 5};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '<' false: " << (printBoolResult(fs, (stl_operator_one < stl_operator_two), (ft_operator_one < ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '<=' true */
	{
		int range_array_one[] = {144, 335, 1, -98, 5};
		int range_array_two[] = {144, 335, 5, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one <= stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one <= ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 1, -98, 5};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '<=' true: " << (printBoolResult(fs, (stl_operator_one <= stl_operator_two), (ft_operator_one <= ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '<=' true equal */
	{
		int range_array_one[] = {144, 335, 5, 0, -54};
		int range_array_two[] = {144, 335, 5, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one <= stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one <= ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '<=' true equal: " << (printBoolResult(fs, (stl_operator_one <= stl_operator_two), (ft_operator_one <= ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '<=' false */
	{
		int range_array_one[] = {144, 9999, 5, 0, -54};
		int range_array_two[] = {144, 335, 5, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one <= stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one <= ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '<=' false: " << (printBoolResult(fs, (stl_operator_one <= stl_operator_two), (ft_operator_one <= ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '>' true */
	{
		int range_array_one[] = {144, 9999, 5, 0, -54};
		int range_array_two[] = {144, 335, 5, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one > stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one > ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 9999, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 5, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '>' true: " << (printBoolResult(fs, (stl_operator_one > stl_operator_two), (ft_operator_one > ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '>' false */
	{
		int range_array_one[] = {144, 335, 5, 0, -54};
		int range_array_two[] = {144, 335, 77, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one > stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one > ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 77, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '>' false: " << (printBoolResult(fs, (stl_operator_one > stl_operator_two), (ft_operator_one > ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '>=' true */
	{
		int range_array_one[] = {144, 335, 78, 0, -54};
		int range_array_two[] = {144, 335, 77, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one >= stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one >= ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 78, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 77, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '>=' true: " << (printBoolResult(fs, (stl_operator_one >= stl_operator_two), (ft_operator_one >= ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* RL '>=' false */
	{
		int range_array_one[] = {144, 335, 5, 0, -54};
		int range_array_two[] = {144, 335, 77, 0, -54};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);
		printVectorAttributes(fs, stl_operator_one, ft_operator_one);
		printVectorAttributes(fs, stl_operator_two, ft_operator_two);

		start_stl();
		if(stl_operator_one >= stl_operator_two){};
		stop_stl();
		start_ft();
		if(ft_operator_one >= ft_operator_two){};
		stop_ft();
		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 77, 0, -54};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_operator_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_operator_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {144, 335, 77, 0, -54};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_operator_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_operator_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "RL '>=' false: " << (printBoolResult(fs, (stl_operator_one >= stl_operator_two), (ft_operator_one >= ft_operator_two)) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	/* Swap */
	{
		int range_array_one[] = {144, 335, 5, 0, -54};
		int range_array_two[] = {47, -98, 58, 611, -4};

		std::vector<int> range_one, range_two;
		for (int i = 0; i < 5; ++i) {
		    range_one.push_back(range_array_one[i]);
		    range_two.push_back(range_array_two[i]);
		}

		std::vector<int>::iterator stl_iterator_beg_one(range_one.begin());
		std::vector<int>::iterator stl_iterator_beg_two(range_two.begin());
		ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));
		ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));

		std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);
		std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);
		ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);
		ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);
		start_stl();
		std::swap(stl_swap_one, stl_swap_two);
		stop_stl();
		start_ft();
		std::swap(ft_swap_one, ft_swap_two);				// change to FT
		stop_ft();

		fs.open("./tester/vectors_output/non_member", std::fstream::in | std::fstream::out | std::fstream::app);

		fs << "\nCode executed:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {47, -98, 58, 611, -4};       \n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "ft::vector<int>::iterator ft_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "ft::vector<int> ft_swap_one(ft_iterator_beg_one, ft_iterator_beg_one + 5);\n";
		fs << "ft::vector<int> ft_swap_two(ft_iterator_beg_two, ft_iterator_beg_two + 5);\n";

		fs << "\nCompared with:\n";
		fs << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯\n";
		fs << "int range_array_one[] = {144, 335, 5, 0, -54};\n";
		fs << "int range_array_two[] = {47, -98, 58, 611, -4};\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_one(&(range_array_one[0]));\n";
		fs << "std::vector<int>::iterator stl_iterator_beg_two(&(range_array_two[0]));\n";
		fs << "std::vector<int> stl_swap_one(stl_iterator_beg_one, stl_iterator_beg_one + 5);\n";
		fs << "std::vector<int> stl_swap_two(stl_iterator_beg_two, stl_iterator_beg_two + 5);\n";
		std::cout << std::setw(30) << std::left << "Swap one: " << std::setw(0) << (printVectorAttributes(fs, stl_swap_one, ft_swap_one) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m") << std::endl;
		std::cout << std::setw(30) << std::left << "Swap two: " << std::setw(0) << (printVectorAttributes(fs, stl_swap_two, ft_swap_two) ? "\033[32m[OK]\033[0m" : "\033[31m[NOP]\033[0m");
		print_speed();
		evaluate_speed(fs);
		fs << "\n**************************************************************\n\n\n\n";
		fs.close();
	}

	std::cout << "\n";
}
