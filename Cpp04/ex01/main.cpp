#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	std::cout << "=== 1. TESTING ANIMAL ARRAY & MEMORY LEAKS ===" << std::endl;

	const int arraySize = 4;
	Animal* animals[arraySize];

	for (int i = 0; i < arraySize; ++i)
	{
		if (i < arraySize / 2)
		{
			animals[i] = new Dog();
		}
		else
		{
			animals[i] = new Cat();
		}
	}

	std::cout << "\nDeleting the array elements..." << std::endl;
	for (int i = 0; i < arraySize; ++i)
	{
		delete animals[i];
	}

	std::cout << "\n === 2. TESTING DEEP COPIES ===" << std::endl;

	Dog basic;
	{
		basic.getBrain()->setIdea(0, "I want to chase a squirrel!");

		Dog tmp = basic;

		std::cout << "tmp's idea: " << tmp.getBrain()->getIdea(0) << std::endl;

		tmp.getBrain()->setIdea(0, "I want to sleep instead.");

		std::cout << "tmp's idea is now: " << tmp.getBrain()->getIdea(0) << std::endl;
		std::cout << "basic's idea is till: " << basic.getBrain()->getIdea(0) << std::endl;

		// tmp goes out of scope here and gets destroyed!
	}

	// If it was a shallow copy, tmp destroying its brain would also destory basic's brain.
	// Let's tese if the basic's brain is still alive and well:
	std::cout << "\nbasic survived tmp's destruction! Idea: " << basic.getBrain()->getIdea(0) << std::endl;

	return 0;
}
