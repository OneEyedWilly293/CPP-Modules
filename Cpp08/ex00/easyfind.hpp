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
// OVERLOAD 1: Non-const container -> returns a regular iterator
// Used when the container is NOT const, allowing you to modify elements.
typename T::iterator easyfind(T& container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(),
			value);

	if (it == container.end())
		throw std::runtime_error("easyfind: value not found in container");

	return it;
}

// OVERLOAD 2: Const container -> returns a const_iterator
// Used when the container IS const (read-only).
// "const T&" means we accept the container as read-only.
// "T::const_iterator" is the read-only iterator type every STL container has.
template <typename T>
typename T::const_iterator easyfind(const T& container, int value)
{
	typename T::const_iterator it = std::find(container.begin(), container.end(),
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
 * On a const container, .begin() and .end() automatically
 * return const_iterators - you cannot modify elements through them.
 *
 * https://en.cppreference.com/w/cpp/algorithm/find.html
 * */
