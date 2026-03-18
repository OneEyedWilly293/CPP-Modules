#pragma once

#include <iostream>
#include <string>
#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern
{
	private:
		// Each one knows how to create ONE specific type of form.
		// We return 'AFomr*' (a pointer) because AForm is an abstract class!
		AForm* makePresidentialPardon(const std::string& target) const;
		AForm* makeRobotomyRequest(const std::string& target) const;
		AForm* makeShrubberyCreation(const std::string& target) const;

	public:
		Intern();
		Intern(const Intern& other);
		Intern& operator=(const Intern& other);
		~Intern();

		AForm* makeForm(const std::string& formName, const std::string& traget) const;
};
