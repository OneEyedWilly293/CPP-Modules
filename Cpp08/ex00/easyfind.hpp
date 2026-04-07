#pragma once

#include <algorithm> // std::find
#include <stdexcept> // std::runtime_error

template <typename T>
typename T::iterator easyfind(T& container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(),
			value);

	if (it == container.end())
		throw std::runtime_error("easyfind: value not found in container");

	return it;
}
