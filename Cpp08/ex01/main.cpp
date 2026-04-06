#include "Span.hpp"
#include <iostream>
#include <vector>
#include <numeric>	// For std::iota - fills a range with sequestial values

int main()
{
	// TEST 1: Basic subject example
	std::cout << "=== Subject Example ===" << std::endl;
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl; // expected: 2

	std::cout << "Longest span: " << sp.longestSpan() << std::endl;	// expected:14


	// TEST 2: Range-based addNumbers with 10,000 integers
	std::cout << "\n=== 10,000 Numbers via Iterator Range ===" << std::endl;

	std::vector<int> bigVec(10000);
	std::iota(bigVec.begin(), bigVec.end(), 0);	// Fill: 0, 1, 2, ..., 9999

	Span bigSpan(10000);
	bigSpan.addNumbers(bigVec.begin(), bigVec.end());	// Bulk insert using iterators

	std::cout << "Shortest span: " << bigSpan.shortestSpan() << std::endl; // expected: 1

	std::cout << "Longest span: " << bigSpan.longestSpan() << std::endl; // expected: 9999


	// TEST 3: Exception - adding to a full span
	std::cout << "\n=== Exception: Span is Full ===" << std::endl;

	try
	{
		sp.addNumber(42);	//sp already has 5/5 numbers(from test 1) - this shoudl throw!
	}
	catch(const std::exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}


	// TEST 4: Exception - not enought numbers for a span
	std::cout << "\n=== Exception: Too Few Numbers ===" << std::endl;

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
