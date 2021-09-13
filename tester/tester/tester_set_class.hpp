#ifndef TESTER_SET_CLASS_HPP
# define TESTER_SET_CLASS_HPP

# include <ctime>
# include <cstdlib>
# include <fstream>
# include <iomanip>
# include <iostream>
# include <set>
# include <string>
# include <sstream>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <vector>
# include "tester.hpp"
# include "utils.hpp"
# include "../containers/set.hpp"

# define NORMAL "\033[0;37m"
# define UNDERLINE "\033[4m"
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"

# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define GREEN "\033[32m"
# define NRM "\033[0m"

# ifdef STRING_SET
#  define FT_TYPE ft::set<std::string>
#  define STL_TYPE std::set<std::string>
#  define INSERT insert_string
#  define REMOVE remove_string
#  define FIND find_string
#  define LOWER lower_string
#  define UPPER upper_string
#  define EQUAL equal_string
#  define VALUE_TYPE std::string
# else
#  define FT_TYPE ft::set<int>
#  define STL_TYPE std::set<int>
#  define INSERT insert_int
#  define REMOVE remove_int
#  define FIND find_int
#  define LOWER lower_int
#  define UPPER upper_int
#  define EQUAL equal_int
#  define VALUE_TYPE int
# endif

# define NUM_PER_LINE 10
# define MINBOOSTED(x, y, z) (z ? x < y : y < x)

void	show_i()
{
	std::cout << GREEN "COMMAND [i]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\ti - insert the value selected\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\ti [OPTIONS] [VALUE]\n";
	std::cout << YELLOW "OPTIONS\n" NRM;
	std::cout << "\t-r (only for integer sets)\n";
	std::cout << "\t\tinsert the range passed as [VALUE];\n";
	std::cout << "\t\tThe range has the form (first_value, last_value) or (first_value, last_value, step)\n";
	std::cout << "\t-rand \n";
	std::cout << "\t\tinsert the random values; the number of items inserted is defined by [VALUE];\n";
	std::cout << YELLOW "EXAMPLES\n" NRM;
	#ifndef STRING_SET
		std::cout << "\tset<int>:\n";
		std::cout << "\t\ti 42\n";
		std::cout << "\t\ti -r (0, 42)\n";
		std::cout << "\t\ti -r (0, 42, 2)\n";
		std::cout << "\t\ti -rand 42\n";
		std::cout << "\t\ti -rand (42, 10, 100) (num_of_numbers, possible_range)\n";
	#else
		std::cout << "\tset<string>:\n";
		std::cout << "\t\ti example\n";
		std::cout << "\t\ti 'example with spaces'\n";
		std::cout << "\t\ti -rand (42, 10)\n";
	#endif
	std::cout << std::endl << std::endl;
}

void	show_r()
{
	std::cout << GREEN "COMMAND [r]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\tr - remove the value selected\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\tr [OPTIONS] [VALUE]\n";
	std::cout << YELLOW "OPTIONS\n" NRM;
	std::cout << "\t-r\n";
	std::cout << "\t\tremove the range passed as [VALUE];\n";
	std::cout << "\t\tThe range has the form (first_value, last_value)\n";
	std::cout << "\t-c\n";
	std::cout << "\t\tremove all values on set;\n";
	std::cout << YELLOW "EXAMPLES\n" NRM;
	#ifndef STRING_SET
		std::cout << "\tset<int>:\n";
		std::cout << "\t\tr 42\n";
		std::cout << "\t\tr -r (0, 42)\n";
		std::cout << "\t\tr -r 42 (erase from 42 till end)\n";
	#else
		std::cout << "\tset<string>:\n";
		std::cout << "\t\tr example\n";
		std::cout << "\t\tr 'example with spaces'\n";
		std::cout << "\t\tr -r (aaaa, bbbbb)\n";
    #endif
	std::cout << std::endl << std::endl;
}

void show_f()
{
	std::cout << GREEN "COMMAND [f]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\tf - find the value selected\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\tf [VALUE]\n";
	std::cout << YELLOW "EXAMPLES\n" NRM;
	#ifndef STRING_SET
		std::cout << "\tset<int>:\n";
		std::cout << "\t\tf 42\n";
	#else
		std::cout << "\tset<string>:\n";
		std::cout << "\t\tf example\n";
		std::cout << "\t\tf 'example with spaces'\n";
	#endif
	std::cout << std::endl << std::endl;
}

void	show_l()
{
	std::cout << GREEN "COMMAND [l]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\tl - find the lower bound of value selected\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\tl [VALUE]\n";
	std::cout << YELLOW "EXAMPLES\n" NRM;
	#ifndef STRING_SET
		std::cout << "\tset<int>:\n";
		std::cout << "\t\tl 42\n";
	#else
		std::cout << "\tset<string>:\n";
		std::cout << "\t\tl example\n";
		std::cout << "\t\tl 'example with spaces'\n";
	#endif
	std::cout << std::endl << std::endl;
}

void	show_u()
{
	std::cout << GREEN "COMMAND [u]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\tu - find the upper bound of value selected\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\tu [VALUE]\n";
	std::cout << YELLOW "EXAMPLES\n" NRM;
	#ifndef STRING_SET
		std::cout << "\tset<int>:\n";
		std::cout << "\t\tu 42\n";
	#else
		std::cout << "\tset<string>:\n";
		std::cout << "\t\tu example\n";
		std::cout << "\t\tu 'example with spaces'\n";
	#endif
	std::cout << std::endl << std::endl;
}

void	show_e()
{
	std::cout << GREEN "COMMAND [e]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\te - find the equal range of value selected\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\te [VALUE]\n";
	std::cout << YELLOW "OPTIONS\n" NRM;
	std::cout << "\t-p\n";
	std::cout << "\t\tprint all numbers of set on range;\n";
	std::cout << "\t\tThe range has the form (first_value, last_value)\n";
	std::cout << YELLOW "EXAMPLES\n" NRM;
	#ifndef STRING_SET
		std::cout << "\tset<int>:\n";
		std::cout << "\t\te 42\n";
	#else
		std::cout << "\tset<string>:\n";
		std::cout << "\t\te example\n";
		std::cout << "\t\te 'example with spaces'\n";
	#endif
	std::cout << std::endl << std::endl;
}

void	show_p()
{
	std::cout << GREEN "COMMAND [p]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\tp - print the set\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\tp [OPTIONS]\n";
	std::cout << YELLOW "OPTIONS\n" NRM;
	std::cout << "\t-t print the set as a tree\n";
	std::cout << "\t-l print the set as a list\n";
}

void	show_h()
{
	std::cout << GREEN "COMMAND [h]\n" NRM;
	std::cout << YELLOW "NAME\n" NRM;
	std::cout << "\th - show the help for the commands\n";
	std::cout << YELLOW "SYNOPSIS\n" NRM;
	std::cout << "\th [VALUES]\n";
	std::cout << YELLOW "POSSIBLE VALUES\n" NRM;
	std::cout << "\ti - insert\n";
	std::cout << "\tr - remove\n";
	std::cout << "\tf - find\n";
	std::cout << "\tl - lower bound\n";
	std::cout << "\tu - upper bound\n";
	std::cout << "\te - equal range\n";
	std::cout << "\tp - print the set\n";
	std::cout << YELLOW "EXAMPLES\n" NRM;
	std::cout << "\th iulp (show the help for i, u, l, p)\n";
}

void	show_help(const std::string &cmd)
{
	std::cout << "\033[2J";
	bool ok = false;
	if (cmd.find('i') != std::string::npos && (ok = true))
		show_i();
	if (cmd.find('r') != std::string::npos && (ok = true))
		show_r();
	if (cmd.find('f') != std::string::npos && (ok = true))
		show_f();
	if (cmd.find('l') != std::string::npos && (ok = true))
		show_l();
	if (cmd.find('u') != std::string::npos && (ok = true))
		show_u();
	if (cmd.find('e') != std::string::npos && (ok = true))
		show_e();
	if (cmd.find('p') != std::string::npos && (ok = true))
		show_p();
	if (!ok)
		show_h();
}

void tokenize(std::string const &str, char delim,
            std::vector<std::string> &out)
{
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

class Tester {
	public:
		Tester() {
			srand(time(0));
		}

		template <class Ta>
		std::string equalContent(
			const std::set<Ta> & stl_map,
			const ft::set<Ta> & ft_map,
			std::ostream &fs = std::cout
		)
		{
			typename ft::set<Ta>::const_iterator ft_it;
			typename std::set<Ta>::const_iterator stl_it;
			if (ft_map.size() != stl_map.size())
				return R_IF("✘", fs == std::cout);
			stl_it = stl_map.begin();
			for(ft_it = ft_map.begin(); ft_it != ft_map.end(); ft_it++)
			{
				if ((*ft_it) != (*stl_it))
				    return R_IF("✘", fs == std::cout);
				stl_it++;
			}
			return G_IF("✔", fs == std::cout);
		}

		template <class Ta>
		bool printSetAttributes(
			std::ostream& fs,
			std::set<Ta>& stl_map,
			ft::set<Ta>& ft_map
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
			std::string content = equalContent(stl_map, ft_map, fs);

			fs << "\n══════════════════════════════════════════════════════════════\n";
			fs << Y_IF("sets attributes : \n", std::cout == fs);
			fs << B_IF("STL : \n", std::cout == fs);
			fs << "Empty       : " << stl_empty  << std::endl;
			fs << "Size        : " << stl_size  << std::endl;
			fs << "Max size    : " << stl_max_size  << std::endl;
			fs << "Content     : [\n";

			typename std::set<Ta>::iterator stl_it;
			int i = 0;
			for (stl_it = stl_map.begin();  stl_it != stl_map.end() && i < 20; ++stl_it, ++i)
			{
				if (!(i % 5)) fs << "	";
				fs << (*stl_it);
				fs << ", ";
				if ((i % 5) == 4) fs << std::endl;
			}
			fs << (i == 20 ? "	..." : "") << "\n]\n";

			fs << std::endl;

			fs << B_IF("FT : \n", std::cout == fs);
			fs << "Empty    [" << equal(ft_empty, stl_empty, fs == std::cout) << "]: " << ft_empty  << std::endl;
			fs << "Size     [" << equal(ft_size, stl_size, fs == std::cout) << "]: " << ft_size  << std::endl;
			fs << "Max size [" << equal(ft_max_size, stl_max_size, fs == std::cout) << "]: " << ft_max_size  << std::endl;

			fs << "Content  [" << content << "]: [\n";

			typename ft::set<Ta>::iterator ft_it;
			i = 0;
			for(ft_it = ft_map.begin(); ft_it != ft_map.end() && i < 20; ++ft_it, ++i)
			{
				if (!(i % 5)) fs << "	";
				fs << (*ft_it);
				fs << ", ";
				if ((i % 5) == 4) fs << std::endl;
			}
			fs << (i == 20 ? "	..." : "") << "\n]\n";

			fs << "══════════════════════════════════════════════════════════════\n";

			/* Error case */
			if (!empty || !size || !max_size || content == R_IF("✘", fs == std::cout))
				return (false);
			return (true);
		}
		#ifndef STRING_SET
		void	elaborate_cmd_i_r(const std::string &cmd, size_t pos_open, size_t pos_close) {
			std::string arg = cmd.substr(pos_open, pos_close - pos_open);
			std::vector<std::string> args;
			std::vector<int> numb;
			tokenize(arg, ',', args);
			if (args.size() > 3 || args.size() < 2)
				throw std::invalid_argument("invalid arguments > 3 || < 2");
			int num;
			for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
				std::stringstream ss;
				num = 0;
				ss << trim(*it);
				ss >> num;
				numb.push_back(num);
			}
			_insert_int_impl(numb);
		}

		void	insert_rand(int num) {
			std::vector<int> v(num);
			v.clear();
			for (int i = 0; i < num; i++)
				v.push_back(rand());
			start_stl();
			stl_set.insert(v.begin(), v.end());
			stop_stl();
			start_ft();
			ft_set.insert(v.begin(), v.end());
			stop_ft();
		}

		void	elaborate_cmd_i_rand_single(const std::string &cmd, size_t pos) {
			if (pos == std::string::npos)
				throw std::invalid_argument("no number found");
			int num;
			std::string arg = cmd.substr(pos, cmd.size() - pos);
			std::stringstream ss;
			ss << trim(arg);
			ss >> num;
			insert_rand(num);
		}

		void	elaborate_cmd_i_rand_ranged(const std::string &cmd, size_t pos_open, size_t pos_close) {
			std::string arg = cmd.substr(pos_open, pos_close - pos_open);
			std::vector<std::string> args;
			std::vector<int> numb;
			tokenize(arg, ',', args);
			if (args.size() != 3)
				throw std::invalid_argument("invalid arguments != 3");
			int num;
			for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
				std::stringstream ss;
				num = 0;
				ss << trim(*it);
				ss >> num;
				numb.push_back(num);
			}
			_insert_int_rand_range_impl(numb);
		}

		void    elaborate_cmd_i_simple(const std::string &cmd) {
		    if (cmd.find_first_of("0123456789") == std::string::npos)
		        throw std::invalid_argument("invalid argument");
		    int num = 0;
		    std::stringstream ss;
		    ss << trim(cmd);
		    ss >> num;
		    _insert_int_single(num);
		}

		void	insert_int(const std::string& cmd) {
			size_t pos_open, pos_close, pos_rand = cmd.find("-rand");
			if ((pos_rand) != std::string::npos) {
				pos_open = cmd.find('(');
				pos_close = cmd.find(')');
				if (pos_open != std::string::npos &&
					(pos_close == std::string::npos || pos_close <= pos_open + 1))
					throw std::invalid_argument("invalid arguments near (");
				if (pos_open == std::string::npos)
					elaborate_cmd_i_rand_single(cmd, cmd.find_first_not_of(WHITESPACE, pos_rand + 5));
				else
					elaborate_cmd_i_rand_ranged(cmd, pos_open + 1, pos_close);
			}
			else if (cmd.find("-r") != std::string::npos) {
				pos_open = cmd.find('(');
				if (pos_open == std::string::npos)
					throw std::invalid_argument("invalid arguments (");
				pos_close = cmd.find(')');
				if (pos_close == std::string::npos || pos_close <= pos_open + 1)
					throw std::invalid_argument("invalid arguments )");
				elaborate_cmd_i_r(cmd, pos_open + 1, pos_close);
			}
			else
			    elaborate_cmd_i_simple(cmd.substr(1));
			printSetAttributes(std::cout, stl_set, ft_set);
			evaluate_speed(std::cout);
		}

		void elaborate_cmd_r_ranged(const std::string &cmd, size_t pos_open, size_t pos_close) {
		    std::string arg = cmd.substr(pos_open, pos_close - pos_open);
		    std::vector<std::string> args;
		    std::vector<int> numb;
		    tokenize(arg, ',', args);
		    if (args.size() != 2)
		        throw std::invalid_argument("invalid arguments != 2");
		    int num;
		    for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
		        std::stringstream ss;
		        num = 0;
		        ss << trim(*it);
		        ss >> num;
		        numb.push_back(num);
		    }
		    _remove_int_range_impl(numb);
		}

		void    elaborate_cmd_r_simple(const std::string &cmd) {
		    if (cmd.find_first_of("0123456789") == std::string::npos)
		        throw std::invalid_argument("invalid argument");
		    int num = 0;
		    std::stringstream ss;
		    ss << trim(cmd);
		    ss >> num;
		    _remove_int_single(num);
		}

		void    elaborate_cmd_r_ranged_end(const std::string &cmd, size_t pos) {
		    if (pos == std::string::npos)
		        throw std::invalid_argument("invalid argument");
		    std::stringstream ss;
		    int num = 0;
		    ss << trim(cmd.substr(pos));
		    ss >> num;
            _remove_int_range_end_impl(num);
		}

		void    remove_int(const std::string &cmd) {
		    size_t pos_open, pos_close, pos_r = cmd.find("-r"), pos_c = cmd.find("-c");
            if (pos_c != std::string::npos) {
                _clear();
            }
		    else if (pos_r != std::string::npos) {
                pos_open = cmd.find('(');
                pos_close = cmd.find(')');
                if (pos_open != std::string::npos &&
                (pos_close == std::string::npos || pos_close <= pos_open + 1))
                    throw std::invalid_argument("invalid arguments near (");
                else if (pos_open != std::string::npos)
                    elaborate_cmd_r_ranged(cmd, pos_open + 1, pos_close);
                else
                    elaborate_cmd_r_ranged_end(cmd, cmd.find_first_of("0123456789"));
            }
		    else
                elaborate_cmd_r_simple(cmd.substr(1));
            printSetAttributes(std::cout, stl_set, ft_set);
            evaluate_speed(std::cout);
		}

		void    find_int(const std::string &cmd) {
		    int num = _get_first_num(cmd);
		    _find_int_impl(num);
		    evaluate_speed(std::cout);
		}

		void    lower_int(const std::string &cmd) {
		    int num = _get_first_num(cmd);
		    _lower_int_impl(num);
		    evaluate_speed(std::cout);
		}

		void    upper_int(const std::string &cmd) {
		    int num = _get_first_num(cmd);
		    _upper_int_impl(num);
		    evaluate_speed(std::cout);
		}

		void    equal_int(const std::string &cmd) {
		    int num = _get_first_num(cmd);
		    _equal_int_impl(num);
		    evaluate_speed(std::cout);
		}

		#else

		void	insert_string(const std::string &cmd) {
			(void)cmd;
		}

		void	remove_string(const std::string &cmd) {
		    (void)cmd;
		}

		void	find_string(const std::string &cmd) {
		    (void)cmd;
		}

		void    lower_string(const std::string &cmd) {
		    (void)cmd;
		}

		void    upper_string(const std::string &cmd) {
		    (void)cmd;
		}

		void    equal_string(const std::string &cmd) {
		    (void)cmd;
		}

		#endif
		void	insert(const std::string &cmd) {
			try {
				INSERT(cmd);
			}
			catch (std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}

		void    remove(const std::string &cmd) {
		    try {
		        REMOVE(cmd);
		    }
		    catch (std::exception &e) {
		        std::cout << e.what() << std::endl;
		    }
		}

		void    find(const std::string &cmd) {
		    try {
		        FIND(cmd);
		    }
		    catch (std::exception &e) {
		        std::cout << e.what() << std::endl;
		    }
		}

		void    lower(const std::string &cmd) {
		    try {
		        LOWER(cmd);
		    }
		    catch (std::exception &e) {
		        std::cout << e.what() << std::endl;
		    }
		}

		void    upper(const std::string &cmd) {
		    try {
		        UPPER(cmd);
		    }
		    catch (std::exception &e) {
		        std::cout << e.what() << std::endl;
		    }
		}

		void    equal_range(const std::string &cmd) {
		    try {
		        EQUAL(cmd);
		    }
		    catch (std::exception &e) {
		        std::cout << e.what() << std::endl;
		    }
		}

		void    print_r(const std::string &cmd, size_t pos_open, size_t pos_close) {
		    std::string arg = cmd.substr(pos_open, pos_close - pos_open);
		    std::vector<std::string> args;
		    std::vector<VALUE_TYPE> numb;
		    tokenize(arg, ',', args);
		    if (args.size() != 2)
		        throw std::invalid_argument("invalid arguments != 2");
		    VALUE_TYPE num;
		    for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it) {
		        std::stringstream ss;
		        num = VALUE_TYPE();
		        ss << trim(*it);
		        ss >> num;
		        numb.push_back(num);
		    }
		    _print_r_impl(numb);
		}

		void    print(const std::string &cmd) {
		    try {
		        size_t pos_open, pos_close;
		        if (cmd.find("-r") != std::string::npos) {
		            pos_open = cmd.find('(');
		            if (pos_open == std::string::npos)
		                throw std::invalid_argument("invalid arguments (");
		            pos_close = cmd.find(')');
		            if (pos_close == std::string::npos || pos_close <= pos_open + 1)
		                throw std::invalid_argument("invalid arguments )");
		            print_r(cmd, pos_open + 1, pos_close);
		        }
		        else
		            ft::printSet<VALUE_TYPE>()(this->ft_set);
		    }
            catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
		}

		void	dispatch_cmd(const std::string &cmd)
		{
			switch (cmd[0])
			{
			case 'h':
				show_help(cmd);
				break;
			case 'i':
				insert(cmd);
				break ;
			case 'r':
				remove(cmd);
				break ;
			case 'f':
				find(cmd);
				break ;
			case 'l':
				lower(cmd);
				break ;
			case 'u':
				upper(cmd);
				break ;
			case 'e':
				equal_range(cmd);
				break ;
			case 'p':
				print(cmd);
				break ;
			case 'q':
				std::cout << "ByeBye" << std::endl;
				throw std::exception();
				break ;
			default:
				std::cout << "unknow command" << std::endl;
				break;
			}
			std::cout << "> ";
			std::cout.flush();
		}

		STL_TYPE& getStlSet() { return stl_set; }
	private:
        std::set<VALUE_TYPE> stl_set;
        ft::set<VALUE_TYPE> ft_set;
        template<class Iterator>
        void    _print_cont(Iterator &begin, Iterator &end) {
            std::cout << "[";
            for (size_t  i = 0; begin != end; ++i) {
                if (!(i % NUM_PER_LINE))
                    std::cout << "\n\t";
                std::cout << *begin << ((++begin) != end ? ", " : "\n");
            }
            std::cout << "]";
        }

        void    _print_r_impl(const std::vector<VALUE_TYPE> &args) {
            if (args[1] < args[0])
                throw std::invalid_argument("invalid argument");
            std::set<VALUE_TYPE>::iterator stl_it_first = stl_set.lower_bound(args[0]), stl_it_last = stl_set.lower_bound(args[1]);
            ft::set<VALUE_TYPE>::iterator ft_it_first = ft_set.lower_bound(args[0]), ft_it_last = ft_set.lower_bound(args[1]);

            std::cout << BLUE"STL range [" << args[0] << ", " << args[1] << ")" NRM << std::endl;
            _print_cont(stl_it_first, stl_it_last);
            std::cout << std::endl << std::endl;
            std::cout << BLUE"FT range [" << args[0] << ", " << args[1] << ")" NRM << std::endl;
            _print_cont(ft_it_first, ft_it_last);
            std::cout << std::endl;
        }
		#ifndef STRING_SET

			int     _get_first_num(const std::string &cmd) {
			    size_t pos = cmd.find_first_of("0123456789");
			    if (pos == std::string::npos)
			        throw std::invalid_argument("invalid argument");
			    std::stringstream ss;
			    int num = 0;
			    ss << trim(cmd.substr(pos));
			    ss >> num;
			    return (num);
			}

			void _insert_int_impl(std::vector<int> &args) {
				(args.size() == 1) ? args.push_back(args[0] + 1) : (void)0;
				(args.size() == 2) ? args.push_back(1) : (void)0;
				if (!args[2] || (args[0] > args[1] && args[2] > 0) || (args[0] < args[1] && args[2] < 0))
				    throw std::invalid_argument("invalid arguments");
				start_stl();
				for(int num = args[0]; MINBOOSTED(num, args[1], args[2] > 0); num += args[2])
					stl_set.insert(num);
				stop_stl();
				start_ft();
				for(int num = args[0]; MINBOOSTED(num, args[1], args[2] > 0); num += args[2])
					ft_set.insert(num);
				stop_ft();
			}

			void	_insert_int_rand_range_impl(std::vector<int> &args) {
				std::vector<int> v(args[0]);
				v.clear();
				for (int i = 0; i < args[0]; ++i)
					v.push_back(rand() % (args[2] - args[1]) + args[1]);
				start_stl();
				stl_set.insert(v.begin(), v.end());
				stop_stl();
				start_ft();
				ft_set.insert(v.begin(), v.end());
				stop_ft();
			}

			void    _insert_int_single(int num) {
			    start_stl();
			    stl_set.insert(num);
			    stop_stl();
			    start_ft();
			    ft_set.insert(num);
			    stop_ft();
			}

			void    _remove_int_range_impl(std::vector<int> &args) {
			    if (args[0] > args[1])
			        throw std::invalid_argument("invalid arguments: on range the first value must be lower than second one");
			    std::set<int>::iterator lbs = (stl_set.lower_bound(args[0])), ubs = (stl_set.upper_bound(args[1]));
			    ft::set<int>::iterator lbf = (ft_set.lower_bound(args[0])), ubf = (ft_set.upper_bound(args[1]));
			    start_stl();
			    stl_set.erase(lbs, ubs);
			    stop_stl();
			    start_ft();
			    ft_set.erase(lbf, ubf);
			    stop_ft();
			}

			void    _remove_int_range_end_impl(int num) {
			    std::set<int>::iterator lbs = (stl_set.lower_bound(num)), ubs = (stl_set.end());
			    ft::set<int>::iterator lbf = (ft_set.lower_bound(num)), ubf = (ft_set.end());
			    start_stl();
			    stl_set.erase(lbs, ubs);
			    stop_stl();
			    start_ft();
			    ft_set.erase(lbf, ubf);
			    stop_ft();
			}

			void    _remove_int_single(int num) {
			    start_stl();
			    stl_set.erase(num);
			    stop_stl();
			    start_ft();
			    ft_set.erase(num);
			    stop_ft();
			}

			void    _clear() {
			    start_stl();
			    stl_set.clear();
			    stop_stl();
			    start_ft();
			    ft_set.clear();
			    stop_ft();
			}

			void    _find_int_impl(int num) {
			    start_stl();
			    std::set<int>::iterator its = stl_set.find(num);
			    stop_stl();
			    start_ft();
			    ft::set<int>::iterator itf = ft_set.find(num);
			    stop_ft();

			    std::cout << "[" << num << "]" << std::endl;
			    std::cout << (its == stl_set.end() ? "founded on" : "not founded on") << " STL set" << std::endl;
			    std::cout << (itf == ft_set.end() ? "founded on" : "not founded on") << " FT set" << std::endl;
			}

			void    _lower_int_impl(int num) {
			    start_stl();
			    std::set<int>::iterator its = stl_set.lower_bound(num);
			    stop_stl();
			    start_ft();
			    ft::set<int>::iterator itf = ft_set.lower_bound(num);
			    stop_ft();
                std::stringstream sss, ssf;
                sss << *its;
                ssf << *itf;
                std::cout << " EVALUATE LOWER BOUND OF [" << num << "]" << std::endl;
			    std::cout << " STL\t" << ((/*its == stl_set.end() || */stl_set.rbegin().base() == its) ? " all less" : sss.str()) << std::endl;
			    std::cout << " FT\t" << (itf == --ft_set.begin() ? "all less" : ssf.str()) << std::endl;
			}

			void    _upper_int_impl(int num) {
			    start_stl();
			    std::set<int>::iterator its = stl_set.upper_bound(num);
			    stop_stl();
			    start_ft();
			    ft::set<int>::iterator itf = ft_set.upper_bound(num);
			    stop_ft();
			    std::stringstream sss, ssf;
			    sss << *its;
			    ssf << *itf;
			    std::cout << " EVALUATE UPPER BOUND OF [" << num << "]" << std::endl;
			    std::cout << " STL\t" << ((its == stl_set.end()) ? " all greater" : sss.str()) << std::endl;
			    std::cout << " FT\t" << (itf == ft_set.end() ? "all greater" : ssf.str()) << std::endl;
			}

			void    _equal_int_impl(int num) {
			    start_stl();
			    std::pair<std::set<int>::iterator, std::set<int>::iterator> its = stl_set.equal_range(num);
			    stop_stl();
			    start_ft();
			    ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> itf = ft_set.equal_range(num);
			    stop_ft();
			    std::stringstream sssl, ssfl, sssu, ssfu;
			    sssl << *(its.first);
			    ssfl << *(itf.first);
			    sssu << *(its.second);
			    ssfu << *(itf.second);
			    std::cout << "EVALUATE EQUAL RANGE OF [" << num << "]" << std::endl;
			    std::cout
			        << " STL\t[" << ((its.first == stl_set.end()) ? "end" : sssl.str())
			        << ", " << ((its.second == stl_set.end()) ? "end" : sssu.str()) << "]" << std::endl;
			    std::cout
			        << " FT\t[" << ((itf.first == ft_set.end()) ? "end" : ssfl.str())
			        << ", " << ((itf.second == ft_set.end()) ? "end" : ssfu.str()) << "]" << std::endl;
			}
		#else

        #endif

};

#endif
