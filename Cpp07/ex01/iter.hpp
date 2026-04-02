#pragma once

#include <cstddef>

/*
 * In older C++, we had to write 'template <typename T, typename F>'.
 * In c++20 we can use simply use 'auto' as a parameter type.
 * This is called an "abbreviated function template".
 * The compiler generate the template for us!
 * void iter(auto* array, const size_t len, auto func)
 * 'auto* array' -> A pointer to an array of ANY type
 * 'const size_t -> The length of the array (const; wont change the length).
 * 'auto func'	 -> ANY function or callable object
 */
template <typename T, typename F>
void iter(T* array, const size_t len, F func)
{
	for (size_t i = 0; i < len; i++)
		func(array[i]);
}
