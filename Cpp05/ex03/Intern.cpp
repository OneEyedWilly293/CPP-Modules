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
	AForm* newForm = new (std::nothrow) PresidentialPardonForm(target);

	if (newForm == nullptr)
	{
		std::cerr << "CRITICAL ERROR: std::bad_alloc triggered. Out of memory!"
			<< std::endl;
	}
	return newForm;
}

AForm* Intern::makeRobotomyRequest(const std::string& target) const
{
	AForm* newForm = new (std::nothrow) RobotomyRequestForm(target);

	if (newForm == nullptr)
	{
		std::cerr << "CRITICAL ERROR: std::bad_alloc triggered. Out of memory!"
			<< std::endl;
	}
	return newForm;
}

AForm* Intern::makeShrubberyCreation(const std::string& target) const
{
	AForm* newForm = new (std::nothrow) ShrubberyCreationForm(target);

	if (newForm == nullptr)
	{
		std::cerr << "CRITICAL ERROR: std::bad_alloc triggered. Out of memory!"
			<< std::endl;
	}
	return newForm;
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
 * =======================================================================
 * 			TRIGGER bad_alloc exception: use in makeRobotomyRequest or others.
 * 	 int* massive_array = new (std::nothrow) int[50000000];

    // If the ulimit blocks it, it returns nullptr
    if (massive_array == nullptr)
    {
        std::cerr << "CRITICAL ERROR: std::bad_alloc triggered. Out of memory!" << std::endl;
        return nullptr; // Return nullptr to main so it safely skips!
    }

    // (If it somehow succeeded, we would clean it up here, but it won't)
    delete[] massive_array;

    // our normal code:
    return new (std::nothrow) RobotomyRequestForm(target);
*/

