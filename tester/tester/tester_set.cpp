#include "tester_set_class.hpp"




int		main(void)
{
	Tester tp;

	std::cout << "\033[2A\r\033[0J"<<  std::endl;
	std::string cmd;
	std::cout << "press :\n";
	std::cout << "\th - help\n";
	std::cout << "\ti - insert\n";
	std::cout << "\tr - remove\n";
	std::cout << "\tf - find\n";
	std::cout << "\tl - lower bound\n";
	std::cout << "\tu - upper bound\n";
	std::cout << "\te - equal range\n";
	std::cout << "\tp - print the set\n";
	std::cout << "\tq - quit\n";
	while (42)
	{
		getline(std::cin, cmd);
		try {
			tp.dispatch_cmd(cmd);
		}
		catch (std::exception &e) {
			exit(0);
		}
	}
}
