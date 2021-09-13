#ifndef UTILS_IN_HPP
# define UTILS_IN_HPP

# include <fstream>
# include <iomanip>
# include <iostream>
# include <string>
# include <sys/time.h>

# include "colors.h"

# define G_IF(str,test) (test ? (std::string(GREEN) + str + NRM) : str)
# define R_IF(str,test) (test ? (std::string(RD) + str + NRM) : str)
# define Y_IF(str,test) (test ? (std::string(YELLOW) + str + NRM) : str)
# define B_IF(str,test) (test ? (std::string(BLUE) + str + NRM) : str)

extern struct timeval t_b_stl, t_b_ft, t_a_stl, t_a_ft;

void start_stl();
void stop_stl();
void start_ft();
void stop_ft();
void evaluate_speed(std::ostream & os);
void print_speed();

#endif
