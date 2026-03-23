#include <iostream>
#include <string>
#include "ScalarConverter.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Please provide exactly one argument.\n";
		std::cout << "Example: ./convert 42.0f\n";
		return 1;
	}

	// Store the input in a string and pass it to our static convert function
	std::string literal = argv[1];
	ScalarConverter::convert(literal);

	return 0;
}
