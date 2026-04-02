#include <iostream>
#include "Array.hpp"

int main()
{
	try
	{
		std::cout << "=== 1. Testing Default Constructor ===" << std::endl;
		Array<int> emptyArray;
		std::cout << "emptyArray size: " << emptyArray.size() << std::endl;


		std::cout << "\n=== 2. Testing Parameterized Constructor ===" << std::endl;
		Array<int> intArray(5);
		std::cout << "intArray size: " << intArray.size() << std::endl;

		// Proving that 'new T[n]()' initialized elements to 0
		std::cout << "intArray[0] initial value: " << intArray[0] << std::endl;

		//Assigning values
		for (unsigned int i = 0; i < intArray.size(); i++)
			intArray[i] = i * 10;
		// intArray is now : [0, 10, 20, 30, 40]

		std::cout << "\n=== 3. Testing Copy Constructor (Deep Copy) ===" << std::endl;
		Array<int> copyArray(intArray);

		// Modify the original array to prove they are separated
		intArray[0] = 999; // now [999, 10, 20, 30, 40]
		std::cout << "intArray[0]: " << intArray[0] << " (Modified)" << std::endl;
		std::cout << "copyArray[0]: " << copyArray[0] << " (Unaffected!)" << std::endl;
		// copyArray should still hold the old intArray values

		std::cout << "\n=== 4. Testing Assignment Operator (Deep Copy) ===" << std::endl;
		Array<int> assignedArray;
		assignedArray = copyArray;

		// Modify the copy to prove they are separated
		copyArray[1] = 888;
		std::cout << "copyArray[1]: " << copyArray[1] << " (Modified)" << std::endl;
		std::cout << "assignedArray[1]: " << assignedArray[1] << " (Unaffected!)" << std::endl;


		std::cout << "\n=== 5. Testing with std::string ===" << std::endl;
		Array<std::string> stringArray(3);
		stringArray[0] = "Hello";
		stringArray[1] = "Templates";
		stringArray[2] = "World";
		for (unsigned int i = 0; i < stringArray.size(); i++)
			std::cout << stringArray[i] << " ";
		std::cout << std::endl;


		std::cout << "\n=== 6. Testing Exeption Handling ===" << std::endl;

		std::cout << "Attempting to access out of bounds index..." << std::endl;
		std::cout << intArray[10] << std::endl; // should throw
	}
	// Since std::exception is the grandparent of ALL standard exceptions, this could catch both:
	// - std::bad_alloc(from new[] failing)
	// = OutOfBoundsException (from operator[])
	catch (const std::exception& e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
	}
	return 0;
}
