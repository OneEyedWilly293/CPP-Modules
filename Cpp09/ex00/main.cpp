#include <iostream>
#include "BitcoinExchange.hpp"

/**
 * @file  main.cpp
 * @brief Entry point for the Bitcoin Exchange program (btc).
 *
 * Usage: ./btc <input_file>
 *
 * Loads the Bitcoin price database from "data.csv", then processes
 * the given input file line by line, printing the value of each
 * Bitcoin amount multiplied by the exchange rate on the given date.
 *
 * @param  argc  Number of command-line arguments (must be 2).
 * @param  argv  argv[1] is the path to the input file.
 * @return 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange btc("data.csv");
		btc.processInput(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
