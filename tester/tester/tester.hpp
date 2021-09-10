#ifndef TESTER_HPP
# define TESTER_HPP

# include <fstream>
# include <iomanip>
# include <iostream>
# include <string>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "utils.hpp"
# include "colors.h"

template <class T>
std::string equal(const T& t1, const T& t2, bool test = false)
{
    return (t1 == t2 ? G_IF("✔", test) : R_IF("✘", test));
}

template <class T>
bool equalbool(const T& t1, const T& t2)
{
    return (t1 == t2 ? true : false);
}

// t1 == stl
// t2 == ft
template<class T>
static bool printSingleValue(std::fstream& fs, const T& t1, const T& t2)
{
    fs << "\n══════════════════════════════════════════════════════════════\n";
    fs << "Value from :\n";
    fs << "STL    : " << t1 << "\n";
    fs << "FT  [" << equal(t1, t2) << "]: " << t2 << "\n";
    fs << "══════════════════════════════════════════════════════════════\n";
    return (t1 == t2 ? true : false);
}

bool printBoolResult(std::fstream& fs, bool stl_bool, bool ft_bool);

void test_vector();
void test_list();
void test_map();
void test_stack();
void test_queue();
void test_deque();

#endif
