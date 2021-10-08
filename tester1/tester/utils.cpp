#include "utils.hpp"

struct timeval t_b_stl, t_b_ft, t_a_stl, t_a_ft;

void start_stl()
{
	gettimeofday(&t_b_stl, 0);
}

void stop_stl()
{
	gettimeofday(&t_a_stl, 0);
}

void start_ft()
{
	gettimeofday(&t_b_ft, 0);
}

void stop_ft()
{
	gettimeofday(&t_a_ft, 0);
}

void evaluate_speed(std::ostream & os)
{
	float diff;
	os << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
	os << Y_IF("Speed Evaluation: ", (std::cout == os)) << std::endl;
	os << std::setw(30) << std::left << "start  stl  => " << std::setw(0) << (t_b_stl.tv_sec * 1000000) + t_b_stl.tv_usec << std::endl;
	os << std::setw(30) << std::left << "end    stl  => " << std::setw(0) << (t_a_stl.tv_sec * 1000000) + t_a_stl.tv_usec << std::endl;
	os << std::setw(30) << std::left << "time   stl  => " << std::setw(0) << "[" << (t_a_stl.tv_sec - t_b_stl.tv_sec) * 1000000 + t_a_stl.tv_usec - t_b_stl.tv_usec << "]" << std::endl;
	os << std::endl;
	os << std::setw(30) << std::left << "start  ft   => " << std::setw(0) << (t_b_ft.tv_sec * 1000000) + t_b_ft.tv_usec << std::endl;
	os << std::setw(30) << std::left << "end    ft   => " << std::setw(0) << (t_a_ft.tv_sec * 1000000) + t_a_ft.tv_usec << std::endl;
	os << std::setw(30) << std::left << "time   ft   => " << std::setw(0) << "[" << (t_a_ft.tv_sec - t_b_ft.tv_sec) * 1000000 + t_a_ft.tv_usec - t_b_ft.tv_usec << "]" << std::endl;
	diff = ((t_a_ft.tv_sec - t_b_ft.tv_sec) * 1000000 + float(t_a_ft.tv_usec - t_b_ft.tv_usec)) * 100 / ((t_a_stl.tv_sec - t_b_stl.tv_sec) * 1000000 +  (float(t_a_stl.tv_usec - t_b_stl.tv_usec) ? float(t_a_stl.tv_usec - t_b_stl.tv_usec) : 1));
	os << "percentage: "<< std::endl
	<< "ft : stl 	=>	[" << diff << "%] [" << ((diff < 2000.0 ) ? G_IF("✔",(std::cout == os)) : R_IF("✘", (std::cout == os))) << "]" << std::endl;
	os << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
}

void print_speed()
{
	float diff;

	diff = float(t_a_ft.tv_usec - t_b_ft.tv_usec) * 100 / (float(t_a_stl.tv_usec - t_b_stl.tv_usec) ? float(t_a_stl.tv_usec - t_b_stl.tv_usec) : 1);
	std::cout << std::endl << "speed ft : stl 	=>	[" << ((diff < 2000.0 ) ? "\033[32m✔" : "\033[31m✘") << "\033[0m]" << std::endl << diff << std::endl << std::endl;
}
