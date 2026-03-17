#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat alice("Alice", 2);
		std::cout << alice << std::endl;

		alice.incrementGrade();
		std::cout << "After promotion: " << alice << std::endl;

		// increment alice grade again (1 goes to 0); INVALID
		// incrementGrade() funcion will 'throw' our custom exception
		alice.incrementGrade();

		//the program instantly leaves our try block and looking for 'catch'
		std::cout << "You will never see this print." << std::endl;
	}
	catch (const std::exception& e)
	{
		// e.what() should print the exact string we defined in the Bureaucrat.cpp file.
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n----------------------------------------" << std::endl;

	std::cout << "Creating Bureaucrat 'Bob' with grade '151'" <<std::endl;
	// let's test our constructor validation
	try
	{
		Bureaucrat bob("Bob", 151);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught for Bob: " << e.what() << std::endl;
	}

	return 0;
}
