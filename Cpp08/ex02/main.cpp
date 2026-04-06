#include <iostream>
#include <list>         // for the second test (replacing MutantStack with std::list)
#include "MutantStack.hpp"

int     main()
{
    // --- Test 1: MutantStack ---
    // This is the exact test from the subject PDF
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
    MutantStack<int>::iterator  it  = mstack.begin();
    MutantStack<int>::iterator  ite = mstack.end();

    ++it; // move forward
    --it; // move backward

    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    // Verify it can be copied into a plain std::stack
    std::stack<int> s(mstack);

	std::cout << "\n=== Test 2: Same output with std::list ===\n";

	// --- Test 2: std::list (should produce the same output) ---
	// running the same test with std::list, outputs must match
	std::list<int> lst;

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
