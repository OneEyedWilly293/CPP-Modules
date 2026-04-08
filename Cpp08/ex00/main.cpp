#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include "easyfind.hpp"

std::ostream& bold_on(std::ostream& os)
{
	return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
	return os << "\e[0m";
}

void printHeader(const std::string& title)
{
	size_t width = title.size() + 8;

	std::string border(width, '=');

	std::cout << bold_on << border << "\n";
	std::cout << bold_on << "=   " << title << "   =" << "\n";
	std::cout << bold_on << border << "\n" << bold_off;
}

int main()
{
	// TEST 1: std::vector
	std::vector<int> vec = {10, 20, 30, 40, 50};
	printHeader("TEST 1 std::vector");
	try
	{
		auto it = easyfind(vec, 30);
		std::cout << "Found: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Test not found - should trigger the exception
	std::cout << "\nSearching for value(exception): 99" << std::endl;
	try
	{
		auto it = easyfind(vec, 99);
		std::cout << "Found: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// TEST 2: std::list
	std::list<int> lst = {100, 200, 300};
	std::cout << "\n";
	printHeader("TEST 2 std::list");

	try
	{
		auto it = easyfind(lst, 200);
		std::cout << "Found: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// TEST 3: std::deque
	std::deque<int> dq = {7, 8, 9};
	std::cout << "\n";
	printHeader("TEST 3 std::deque");

	try
	{
		auto it = easyfind(dq, 9);
		std::cout << "Found: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// TEST 4: const container (const_iterator)
	// This test verifies that easyfind works on a READ-ONLY (const) container.
	// A const container forces the compiler to use "const_iterator" instead of
	// "iterator". If your easyfind only handles T&, this test won't even compile.
	std::cout << "\n";
	printHeader("Testing const std::vector");

	// The container is const - its values can NEVER be modified after this line.
	const std::vector<int> constVec = {3, 14, 15, 92, 65, 35};
	std::vector<int> constTests = {14, 92, 0, 7, 65, 100};

	/* ranged-based for loop(C++11)
	 * val: a fresh variable created to hold each element, one at a time
	 * ":" - the colon means "in"; read as "for each val IN constTests"
	 * constTests: The container to loop through
	 *
	 * Old way: manual index, verbose
	 * for (size_t i = 0; i < constTests.size(); i++)
	 * {
	 * 		int val = constTests[i];
	 * 		// use val...
	 * }
	 */
	for (int val : constTests)
	{
		try
		{
			// We can dereference it to READ the value, but we cannot write to it.
			// e.g. *it = 99 would be a compile error(which is correct behaviour).
			typename std::vector<int>::const_iterator it = easyfind(constVec, val);
			std::cout << "Found: " << *it << "\n";
		}
		catch(const std::exception& e)
		{
			std::cout << "Error: " << e.what() << '\n';
		}
	}

	return 0;
}
