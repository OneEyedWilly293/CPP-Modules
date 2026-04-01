#include <iostream>
#include "iter.hpp"

template <typename T>
void print(const T& element)
{
	std::cout << element << std::endl;
}

void doubleIt(int& element)
{
	element *= 2;
}

int main()
{
	// Test 1: int array with print
	int ints[] = {1, 2, 3, 4, 5};
	std::cout <<  "== Test 1: int array ==" << std::endl;
	iter(ints, 5, print<int>);

	// Test 2: string array with print
	std::string words[] = {"hello", "world", "templates"};
	std::cout << "\n== Test 2: string array with print ==" << std::endl;
	iter(words, 3, print<std::string>);

	// Test 3: modifying elements(non-const)
	// doubleIt takes a non-const reference, so it
	// modifies each element directly in the array.
	std::cout << "\n== Test 3: doubled ints ==" << std::endl;
	iter(ints, 5, doubleIt);
	iter(ints, 5, print<int>);

	// Test 4: const array (read-only)
	// iter works on const arrays too - the function
	// passed must accept a const reference in this case.
	const int consts[] = {10, 20, 30};
	std::cout << "\n== Test 4: const int array ==" << std::endl;
	iter(consts, 3, print<int>);

	return 0;
}
