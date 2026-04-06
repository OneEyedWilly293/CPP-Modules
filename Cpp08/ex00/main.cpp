#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

int main()
{
	// TEST 1: std::vector
	std::vector<int> vec = {10, 20, 30, 40, 50};

	std::cout << "=== Testing std::vector ===" << std::endl;

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

	std::cout << "\n=== Testing std::list ===" << std::endl;

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

	std::cout << "\n=== Testing std::deque ===" << std::endl;

	try
	{
		auto it = easyfind(dq, 9);
		std::cout << "Found: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
