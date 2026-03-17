#include "Bureaucrat.hpp"
#include "Form.hpp"

std::ostream& bold_on(std::ostream& os)
{
	return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
	return os << "\e[0m";
}

int main()
{
	std::cout << "-------------------------------------------------------------\n";
	std::cout << bold_on << "	TEST 1: Form Creation & Grade Validation" << bold_off << std::endl;
	std::cout << "-------------------------------------------------------------\n";

	try
	{
		// basic Form that anyone can sign (requires grade 150)
		Form coffeeAForm("Coffee Request", 150, 150);
		std::cout << "Successfully created: " << coffeeAForm << std::endl;

		// This should throw and error because 0 is an invalid grade (highest is 1)
		std::cout << "Attempting to create an invalid Form..." << std::endl;
		Form invalidAForm("Illegal Form", 0, 50);

		// Because the exception is thrown above, the program jumps to 'catch'.
		std::cout << "You will never see this line." << std::endl;
	}
	catch (const std::exception& e)
	{
		// catching the Form::GradeTooHighException
		std::cout << "Exception caught: " << e.what() << std::endl;
	}


	std::cout << "\n-------------------------------------------------------------\n";
	std::cout << bold_on << "	TEST 2: THe Intern and the Top Secret Document" << bold_off << std::endl;
	std::cout << "-------------------------------------------------------------\n";

	try
	{
		Bureaucrat intern("The Intern", 150);
		Bureaucrat ceo("The CEO", 1);

		// We create a highly classified document.
		// It requires a high rank of 10 to sign, and even higher rank of 5 to execute.
		Form secretDoc("Top Secret Document", 10, 5);

		std::cout << intern << std::endl;
		std::cout << ceo << std::endl;
		std::cout << secretDoc << std::endl;
		std::cout << "\n--- Action Starts ---" << std::endl;

		// We make intern attempt to sign the classified document.
		// Since his grade is worse than the required grade(10) it should print failure message!
		intern.signAForm(secretDoc);

		// Let's prove the Form is still unsigned.
		std::cout << "Status after Intern: " << secretDoc << std::endl;

		// Now we make CEO step in to sign the classified document.
		// Since his grade(1) is better than the required grade(10) this should print success message!
		ceo.signAForm(secretDoc);

		// Let's prove the Form is now signed.
		std::cout << "Status after CEO: " << secretDoc << std::endl;
	}
	catch (const std::exception& e)
	{
		// We shouldn't hit this catch block beacuse our signAForm() funcion
		// internally handles the try-catch for the signinig process!
		// But it's considered as good practice to wrap object creation in a try-catch.
		std::cout << "Critical Error: " << e.what() << std::endl;
	}


	std::cout << "\n-------------------------------------------------------------\n";
	std::cout << bold_on << "	TEST 3: The Intern's Redemption" << bold_off << std::endl;
	std::cout << "-------------------------------------------------------------\n";

	try
	{
		Bureaucrat intern("The Intern", 150);
		Form coffeeAForm("Coffee Request Form", 150, 150);

		// since the coffee Form requires grade 150, the intern is allowed to sign it!
		intern.signAForm(coffeeAForm);
		std::cout << coffeeAForm << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Critical Error: " << e.what() << std::endl;
	}
	return 0;
}
