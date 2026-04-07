#pragma once

#include <algorithm> // std::find
#include <stdexcept> // std::runtime_error

/*
 * "typename T::iterator" is the return type.
 *	- Every STL container has a nested type called "interator".
 *	- e.g., std::vector<int>::iterator, std::list<int>::iterator
 *	- We use "typename" here to tell the compiler: "this IS a type" (to prevent panic)
 *	- By default(compiler) assumes it's a variable(which breaks everything).
 *
 * Parameters:
 * 	T& container	-> a reference to any container of integers
 *  int value		-> the number we're searching for
 * */
template <typename T>
typename T::iterator easyfind(T& container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(),
			value);

	if (it == container.end())
		throw std::runtime_error("easyfind: value not found in container");

	return it;
}


/*
 * std::find scans the range [container.begin(), container.end())
 * and returns an iterator pointing to the FIRST match.
 *
 * If the value is NOT found, it returns container.end().
 * container.end() is NOT a valid element - it's a sentinel; "past the end of the container."
 *
 * If value IS found
 * We return the iterator pointing directly to that element.
 * The caller can derefence it with *it to get the value.
 *
 * https://en.cppreference.com/w/cpp/algorithm/find.html
 * */
