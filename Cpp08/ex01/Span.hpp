#pragma once

#include <vector>
#include <stdexcept>	// For std::overflow_error and std::logic_error
#include <algorithm>	// For std::sort, std::min_element, std::max_element
#include <numeric>		// For std::adjacent_difference (used in shortestSpan)
#include <iterator>		// For std::distance (used in addNumbers range check)
#include <climits>		// For INT_MAX

class Span
{
	private:
		unsigned int		_maxSize;	//maximum store size of ints
		std::vector<int>	_numbers;	// Where we actually store the integers

	public:
		// OCF
		Span(unsigned int n);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();
		// Deconstructor: nothing to manually free since std::vector handles its own memory).

		// Adds a single integer. Throws if already at max capacity.
		void addNumber(int number);

		/*
		 * RANGE-BASED addNumbers: accepts any two iterators (begin, end)
		 * and bulk-inserts all values between them into _numbers.
		 * This is a TEMPLATE because iterators can come from any STL container
		 * (vector, list, array, etc.); for flexibility.
		 *
		 * Template functions MUST be defined in the header file because
		 * the compiler needs to see the full definition to generate code for
		 * whatever type you pass in.
		 * https://en.cppreference.com/w/cpp/language/function_template
		 */
		template <typename Iterator>
		void addNumbers(Iterator begin, Iterator end)
		{
			if (_numbers.size() + static_cast<size_t>(std::distance(begin, end))
					> _maxSize)
				throw std::overflow_error("Cannot add: would exceed Span capacity");
			_numbers.insert(_numbers.end(), begin, end);
		}

		// Returns the smallest difference between any two stored numbers
		int shortestSpan() const;

		// Returns the largest difference betweem any two stored numbers
		int longestSpan() const;
};

/*
 * std::distance counts how many elements are between begin and end
 * We check: current size + incoming elements <= max capactiy.
 *
 * std::vector::insert with iterators bulk-copies all the elements at once.
 * This is WAY faster than calling addNumber() 10,000 times in a loop!
 * https://en.cppreference.com/w/cpp/container/vector/insert
 * https://en.cppreference.com/w/cpp/container/vector
 */
