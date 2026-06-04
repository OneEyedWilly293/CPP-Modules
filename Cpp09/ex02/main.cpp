#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./PmergeMe <positive integers...>\n";
		return 1;
	}
	try
	{
		PmergeMe pm;
		pm.parseArgs(argc, argv);
		pm.run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}
	return 0;
}
