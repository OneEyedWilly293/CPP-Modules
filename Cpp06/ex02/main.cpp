#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Base.hpp"

// Let's try a catch errors any error that "bubble up" at the highest level
int main()
{
	// Seed the random number generateor using the current time
	// This ensures we get different random classes every time we run the program
	std::srand(std::time(NULL));

	try
	{
		// Generate a random object
		Base* random_obj = generate();

		std::cout << "Identifying via pointer: ";
		identify(random_obj);

		std::cout << "Identifying via reference: ";
		// We dereference the pointer using '*' to pass it as a reference
		identify(*random_obj);

		delete random_obj;
	}

	// catch bubbled-up error before the program ends.
	catch (const std::bad_alloc& e)
	{
		// gracefully handle in one central location.
		std::cerr << "CRITICAL ERROR: Out of memory! (" << e.what() << ")\n";
		return 1;
	}
	catch (const std::exception& e)
	{
		// we can catch other unexpected standard exceptions here, just in case.
		std::cerr << "An unexpected error occurred: " << e.what() << "\n";
		return 1;
	}
	return 0;
}
