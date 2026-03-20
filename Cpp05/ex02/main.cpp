#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include <ctime> // for time()

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

void printSubTitle(const std::string& title)
{
	std::cout << "--- " << bold_on << title << bold_off << " ---" << std::endl;
}

int main()
{
	//20.03: Seed the random number EXACTLY ONCE at the start of the program
	std::srand(std::time(nullptr));

	printTestTitle("TEST: Bureaucrats and the Three Forms");

	try
	{
		Bureaucrat ceo("The CEO", 1);
		Bureaucrat mid("Mid Manager", 50);
		Bureaucrat intern("The Intern", 150);

		ShrubberyCreationForm shrub("Home");
		RobotomyRequestForm robot("Bender");
		PresidentialPardonForm pardon("Alice");

		printSubTitle("1. Intern Tries to Plant a Shrubbery");
		// Intern tries to sign and execute (both should fail)
		intern.signForm(shrub);
		intern.executeForm(shrub);

		std::cout << "\n";
		printSubTitle("2. Mid Manager Steps In");
		// Mid manager signs the shrubbery, then executes it (creates the file)
		mid.signForm(shrub);
		mid.executeForm(shrub);

		// Mid manager tries to handle the Robotomy
		mid.signForm(robot); // succeeds (needs 72, has 50)
		mid.executeForm(robot); // Fails (needs 45, has 50)

		std::cout << "\n";
		printSubTitle("3. CEO Handles the Rest");
		// CEO executes the robotomy that the Mid Manager signed
		ceo.executeForm(robot);

		// CEO signs and executes the Presidential Pardon
		ceo.signForm(pardon);
		ceo.executeForm(pardon);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}
