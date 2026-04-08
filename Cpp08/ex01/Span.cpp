#include "Span.hpp"

// Parametized constructor: just saves the max size. The vector start empty by default.
Span::Span(unsigned int n) : _maxSize(n)
{
}

// Copy constructor: copies both the max size AND all stored numbers
Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers)
{
}

// Copy assignment: same as copy constructor, but we check for self-assignment
Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_maxSize = other._maxSize;
		_numbers = other._numbers;
	}
	return *this;
}

// Deconstructor: nothing to manually clean up(std::vector handles its own memory)
Span::~Span()
{
}

// push_back adds the number to the end of the vector
void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw std::overflow_error("Span is full: cannot add more numbers");
	_numbers.push_back(number);
}

int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw std::logic_error("Need at least 2 numbers to find a span");
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());

	int shortest = INT_MAX;
	for (size_t i = 1; i < sorted.size(); i++)
	{
		int diff = sorted[i] - sorted[i - 1];
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

// The longest span is simply: MAX value - MIN value
// std::max_element / std::min_element return ITERATORS, so we dereference with *
// https://en.cppreference.com/w/cpp/algorithm/max_element
int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw std::logic_error("Need at least 2 numbers to find a span");

	int maxVal = *std::max_element(_numbers.begin(), _numbers.end());
	int minVal = *std::min_element(_numbers.begin(), _numbers.end());

	return maxVal - minVal;
}
