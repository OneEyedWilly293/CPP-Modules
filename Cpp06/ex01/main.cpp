#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
	Data myData;
	myData.id = 42;
	myData.name = "Arthur Dent";

	std::cout << "Original Data address: " << &myData << "\n";
	std::cout << "Original Data values: id = " << myData.id << ", name = "
				<< myData.id << "\n\n";

	// Serialize the pointer into a raw integer
	auto raw_integer = Serializer::serialize(&myData);
	std::cout << "Serialized integer: " << raw_integer << "\n\n";

	// Deserialize the integer back into a pointer
	auto deserialized_ptr = Serializer::deserialize(raw_integer);
	std::cout << "Deserialized address: " << deserialized_ptr << "\n";

	// Verify it worked by checking the values inside the deserialized pointer
	if (deserialized_ptr == &myData)
	{
		std::cout << "SUCCESS! The addresses match.\n";
		std::cout << "Recovered values: id = " << deserialized_ptr->id
				<< ", name = " << deserialized_ptr->name << "\n";
	}
	else
	{
		std::cout << "FAILURE! The addresses do not match.\n";
	}
	return 0;
}
