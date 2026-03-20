#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include <ctime>

std::ostream& bold_on(std::ostream& os)
{
	return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
	return os << "\e[0m";
}

void printTestTitle(const std::string& title)
{
	std::cout << "\n-----------------------------------------------------------"
		<< std::endl;
	std::cout << "	" << bold_on << title << bold_off << std::endl;
	std::cout << "-----------------------------------------------------------"
		<< std::endl;
}

int main()
{
	//20.03: Set the seed just ONCE when the program starts(actual 50/50 randomness!)
	std::srand(std::time(nullptr));
	printTestTitle("TEST: The Intern creates forms");

	Intern someRandomIntern;
	Bureaucrat ceo("The CEO", 1);

	AForm* rrf = nullptr;	// A pointer to hold the robotomy form
	AForm* ppf = nullptr;	// A pointer to hold the Pardon form
	AForm* fail = nullptr;	// A pointer to test an invalid form

	// 1. Success: Intern creates a Robotomy form
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	// because we know it will return nullptr if it fails (instead of crashing),
	// we just use if statement to check.
	if (rrf != nullptr)
	{
		// We only execute the form if the memory was successfully allocated
		ceo.signForm(*rrf);
		ceo.executeForm(*rrf);
		delete rrf;
	}

	// 2. Success: Intern creates a Pardon form
	ppf = someRandomIntern.makeForm("presidential pardon", "Alice");
	if (ppf)
	{
		ceo.signForm(*ppf);
		ceo.executeForm(*ppf);
		delete ppf;
	}

	printTestTitle("TEST: Intern fails to create form");

	// 3. Failure: Invalid form name
	fail = someRandomIntern.makeForm("coffee request", "Boss");
	if (fail)
	{
		delete fail;	// this will never run because fail will be NULL
	}

	return 0;
}
