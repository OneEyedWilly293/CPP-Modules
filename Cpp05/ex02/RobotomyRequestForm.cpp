#include "RobotomyRequestForm.hpp"
#include <cstdlib> // for rand() and srand()

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("Robotomy Request Form", 72, 45), m_target("Default")
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
	: AForm("Robotomy Request Form", 72, 45), m_target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
	: AForm(other), m_target(other.m_target)
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		this->m_target = other.m_target;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

void RobotomyRequestForm::performAction() const
{
	std::cout << "* BZZZZT! WHIRRRRR! LOUD DRILLING NOISES! *" << std::endl;

	// rand() % 2 generates either a 0 or a 1 (50% chance for each)
	if (std::rand() % 2 == 0)
	{
		std::cout << this->m_target << " has been robotomized successfully!" << std::endl;
	}
	else
	{
		std::cout << "Robotomy on " << this->m_target << " failed miserably." << std::endl;
	}
}
