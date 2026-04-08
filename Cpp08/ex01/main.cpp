#include "Span.hpp"
#include <iostream>
#include <vector>
#include <numeric>	// For std::iota - fills a range with sequestial values

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
	// TEST 1: Basic subject example
	printHeader("TEST 1: Subject Example");
	std::cout << "Creating a Span size of 5" << std::endl;
	Span sp = Span(5);

	std::cout << "Adding numbers to Span: 6, 3, 17, 9, 11" << std::endl;
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "\n --- Results ---\n";
	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl; // expected: 2

	std::cout << "Longest span: " << sp.longestSpan() << std::endl;	// expected:14


	// TEST 2: Range-based addNumbers with 10,000 integers
	std::cout << "\n";
	printHeader("TEST 2: 10,000 Numbers via Iterator Range");
	std::vector<int> bigVec(10000);
	std::cout << "filling the range sequentially increasing values(std::iota)\n";
	std::iota(bigVec.begin(), bigVec.end(), 0);	// Fill: 0, 1, 2, ..., 9999

	std::cout << "Creating bigSpan to bulk insert using iterator...\n";
	Span bigSpan(10000);
	bigSpan.addNumbers(bigVec.begin(), bigVec.end());	// Bulk insert using iterators

	std::cout << "\n --- Results ---\n";
	std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl; // expected: 1

	std::cout << "Longest span: " << bigSpan.longestSpan() << std::endl; // expected: 9999
	std::cout << "\n";

	// TEST 3: Exception - adding to a full span
	printHeader("TEST 3: Exception - adding to a full span");
	std::cout << "trying to add number 42 to Span created from TEST 1(should throw)" << std::endl;
	std::cout << "\n --- Results ---\n";
	try
	{
		sp.addNumber(42);	//sp already has 5/5 numbers(from test 1) - this shoudl throw!
	}
	catch(const std::exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}


	// TEST 4: Exception - not enough numbers for a span
	std::cout << "\n";
	printHeader("TEST 4: Exception - Too Few Numbers");
	// std::cout << "\n=== Exception: Too Few Numbers ===" << std::endl;
	std::cout << "Creating a tiny Span and adding only 1 number(cant calculate a span!)" << std::endl;
	std::cout << "\n --- Results ---\n";
	try
	{
		Span tiny(10);
		tiny.addNumber(42);	// Only 1 number - cant calcuate a span!
		std::cout << tiny.shortestSpan() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}

	return 0;
}
