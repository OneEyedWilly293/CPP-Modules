#pragma once

#include <iostream>

template <typename T>
void swap(T& a, T& b)
{
	// auto temp = a;
	// a = b;
	// b = temp;
	T tmp = a;
	a = b;
	b = tmp;
}

// le ternary (condition ? value_if_true : value_if_false)
// this should naturally handles the "if equal, return b" rule
template <typename T>
const T& min(const T& a, const T& b)
{
	return (a < b) ? a : b;
}

template <typename T>
const T& max(const T& a, const T& b)
{
	return (a > b) ? a : b;
}
