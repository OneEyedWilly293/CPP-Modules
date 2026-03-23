#include <iostream>
#include <cstdlib> // for std::rand() and srand()
#include <ctime>	// for std::time()
#include <exception>

#include "Base.hpp"

/*
 * generate()
 * Randomly instantiates A, B, or C and returns it as a Base pointer.
 */
Base* generate(void)
{
	// Generate a drandom number between 0 and 2
	int random_val = std::rand() % 3;

	// Depending on the number, create and return a different derived class.
	if (random_val == 0)
	{
		return new A();
	}
	if (random_val == 1)
	{
		return new B();
	}
	return new C();
}

/*
 * identify(Base* p)
 * Uses dynamic_cast to figure out the actual type of the pointer.
 * If dynamic_cast fails with pointers, it returns nullptr.
 */
void identify(Base* p)
{
	// We try casting the Base pointer to an A pointer.
	// If it succeeds, 'p' was actually pointing to an A object.
	if (dynamic_cast<A*>(p))
	{
		std::cout << "A\n";
	}
	// If it wasnt't an A, we try casting to B.
	else if (dynamic_cast<B*>(p))
	{
		std::cout << "B\n";
	}
	else if (dynamic_cast<C*>(p))
	{
		std::cout << "C\n";
	}
}

/*
 * identify(Base& p)
 * Uses dynamic_cast on a reference. Since references cannot be null,
 * a failed cast throws an exception; we must use try-catch blocks.
 * strictly forbidden from using pointers inside this function.
 */
void identify(Base& p)
{
	// Try casting to A reference
	try
	{
		// We cast 'void' to suppress "unused variable" warning; only care if cast succeeds.
		(void)dynamic_cast<A&>(p);
		std::cout << "A\n";
		return;
	}
	catch (const std::exception& e)
	{
	}

	// try casting to B ref
	try
	{
		(void)dynamic_cast<B&>(p);
		std::cout << "B\n";
		return;
	}
	catch (const std::exception& e)
	{
	}

	//try c
	try
	{
		(void)dynamic_cast<C&>(p);
		std::cout << "C\n";
		return;
	}
	catch(const std::exception& e)
	{
	}
}
