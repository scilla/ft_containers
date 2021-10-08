#include <iostream>
#include <string>
#include <deque>
#if TESTSTL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
	#define _container c
#else
	#include "./srcs/map.hpp"
	#include "./srcs/stack.hpp"
	#include "./srcs/vector.hpp"
#endif
#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT ((MAX_RAM/2) / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->_container = rhs._container;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->_container.begin(); }
	iterator end() { return this->_container.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;

	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_int.push_back(i);
	}

	ft::vector<int> vector_int2(vector_int);

	for (int i = 0; i < COUNT; i++)
	{
		if (!(i % 3))
			vector_int[i] = 5;
	}
	
	for (size_t i = 0; i < vector_int.size(); i++)
		std::cout << vector_int[i] << std::endl;

	std::cout << std::endl;

	vector_int.swap(vector_int2);

	for (size_t i = 0; i < vector_int.size(); i++)
		std::cout << vector_int[i] << std::endl;

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 1000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	// silenced cause fails on ubuntu
	// std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}
