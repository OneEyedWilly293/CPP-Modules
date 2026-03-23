#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"

int main()
{
	// Seed the random number generateor using the current time
	// This ensures we get different random classes every time we run the program
	std::srand(std::time(NULL));

	// Generate a random object
	Base* random_obj = generate();

	std::cout << "Identifying via pointer: ";
	identify(random_obj);

	std::cout << "Identifying via reference: ";
	// We dereference the pointer using '*' to pass it as a reference
	identify(*random_obj);

	delete random_obj;

	return 0;
}
