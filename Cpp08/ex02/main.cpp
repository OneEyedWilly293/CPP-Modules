#include <iostream>
#include <list>         // for the second test (replacing MutantStack with std::list)
#include "MutantStack.hpp"

std::ostream& bold_on(std::ostream& os)
{
	return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
	return os << "\e[0m";
}

void printHeader(const std::string& title)
{
	size_t width = title.size() + 8;

	std::string border(width, '=');

	std::cout << bold_on << border << "\n";
	std::cout << bold_on << "=   " << title << "   =" << "\n";
	std::cout << bold_on << border << "\n" << bold_off;
}

int     main()
{
    // --- Test 1: MutantStack ---
    // This is the exact test from the subject PDF
	printHeader("TEST 1: MutantStack(Subject sample)");
    MutantStack<int>    mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl; // prints: 17

    mstack.pop(); // removes 17

    std::cout << mstack.size() << std::endl; // prints: 1

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Now we use iterators to loop through the stack — bottom to top
    MutantStack<int>::iterator  it  = mstack.begin(); // "it" points to the BOTTOM element(5)
    MutantStack<int>::iterator  ite = mstack.end();	// "ite" ponts one-past the TOP (0)

    ++it; // move forward(now points to 3)
    --it; // move backward(back to 5)

    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    // Verify it can be copied into a plain std::stack
	/*
	 * Can a regular std::stack be constructed from a MutantStack?
	 * YES -> compiles fine (MutantStack IS-A std::stack; thanks to inheritance)
	 * NO -> compiler error (would mean inheritance is broken).
	 */
    std::stack<int> s(mstack);

	std::cout << "\n";
	printHeader("TEST 2: Same output with std::list");
	// running the same test with std::list, outputs must match
	std::list<int> lst;	//std::list is a doubly-linked list - it naturally supports iterators

	lst.push_back(5);
	lst.push_back(17);

	std::cout << lst.back() << std::endl;	// 17

	lst.pop_back();

	std::cout << lst.size() << std::endl;	// 1

	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator	it2 = lst.begin();
	std::list<int>::iterator	ite2 = lst.end();

	++it2;
	--it2;

	while (it2 != ite2)
	{
		std::cout << *it2 << std::endl;
		++it2;
	}
	return (0);
}
