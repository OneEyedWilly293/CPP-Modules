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

	return 0;
}
