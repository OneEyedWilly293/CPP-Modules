#include <iostream>
#include "whatever.hpp"

/*
 * '::' is the scope resolution operator.
 * It tells the compiler: "use MY swap/min/max
 * from the global scope, not std::swap etc."
 */
int main()
{
	int a = 2;
	int b = 3;

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

	std::cout << "\n---- ADDITIONAL TESTS ----\n";
	// Both min and max must return the SECOND parameter(f)
	std::cout << "\n== Edge case 1: Equal values ==\n";
	int e = 5, f = 5;
	std::cout << "min(5, 5) = " << ::min(e, f) << std::endl;
	std::cout << "max(5, 5) = " << ::max(e, f) << std::endl;

	// Swapping a variable with itself should do nothing
	std::cout << "\n== Edge case 2: Self-swap ==\n";
	int g = 42;
	std::cout << "before swap: g = " << g << std::endl;
	::swap(g, g);
	std::cout << "after swap(g, g): g = " << g << std::endl;

	std::cout << "\n== Edge case 3: negative numbers ==\n";
	int h = -5;
	int i = -3;
	std::cout << "min(-5, -3) = " << ::min(h, i) << std::endl;
	std::cout << "max(-5, -3) = " << ::max(h, i) << std::endl;

	std::cout << "\n== Edge case 4: Floats ==\n";
	// Templates work with any comparable type, including float
	float j = 1.1f;
	float k = 1.2f;
	std::cout << "before swap: j = " << j << ", k = " << k << std::endl;
	::swap(j, k);
	std::cout << "after swap: j = " << j << ", k = " << k << std::endl;
	std::cout << "min(j, k) = " << ::min(j, k) << std::endl;
	std::cout << "max(j, k) = " << ::max(j, k) << std::endl;

	/* Mixed Types (Compile Error - by design)
	 * ::mix(1, 2.0) !! wont compile; T cant be both int and double
	 *	==========================================================
	 * Non-Comparable Types(Compile Error)
	 * struct Foo {};
	 * Foo x, y;
	 * ::min(x, y)	!! wont compile; Foo has no operator<
	 */

	return 0;
}
