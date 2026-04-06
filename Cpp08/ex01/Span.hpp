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
		unsigned int		_maxSize;
		std::vector<int>	_numbers;

	public:
		// OCF
		Span(unsigned int n);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		void addNumber(int number);

		template <typename Iterator>
		void addNumbers(Iterator begin, Iterator end)
		{
			if (_numbers.size() + static_cast<size_t>(std::distance(begin, end))
					> _maxSize)
				throw std::overflow_error("Cannot add: would exceed Span capacity");
			_numbers.insert(_numbers.end(), begin, end);
		}

		int shortestSpan() const;

		int longestSpan() const;
};
