#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern& other)
{
	(void)other;
}

Intern& Intern::operator=(const Intern& other)
{
	(void)other;
	return *this;
}

Intern::~Intern()
{
}

AForm* Intern::makePresidentialPardon(const std::string& target) const
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeRobotomyRequest(const std::string& target) const
{
	return new RobotomyRequestForm(target);
}

AForm* Intern::makeShrubberyCreation(const std::string& target) const
{
	return new ShrubberyCreationForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
	// We define an array of the 3 valid form names
	std::string formNames[3] = {
		"presidential pardon",
		"robotomy request",
		"shrubbery creation"
	};

	// We define an array of Pointers to Member functions.
	AForm* (Intern::*formCreators[3])(const std::string&) const = {
		&Intern::makePresidentialPardon,
		&Intern::makeRobotomyRequest,
		&Intern::makeShrubberyCreation
	};

	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;

			// We call the matching function from the other array.
			// 'this->*' is required syntax to call a member function pointer.
			return (this->*formCreators[i])(target);
		}
	}
	// If no watch is found after the loop finishes, we print an erro and return NULL.
	std::cout << "Intern couldn't create " << formName
		<< " because the form name does not exist!" << std::endl;
	return nullptr;
}


/*
 * The tradutional 'try-catch' Block

 	AForm* Intern::makePresidentialPardon(const std::string& target) const
	{
		try {
			// Attempt to allocate memory
			return new PresidentialPardonForm(target);
		}
		catch (const std::bad_alloc& e) {
			// If out of memory, print the error and safely return nullptr
			std::cerr << "Memory allocation failed: " << e.what() << std::endl;
			return nullptr;
	}
}
*/

