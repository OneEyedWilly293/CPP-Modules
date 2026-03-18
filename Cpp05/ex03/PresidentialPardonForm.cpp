#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() :
	AForm("Presidential Pardon Form", 25, 5), m_target("Default")
{
}
PresidentialPardonForm::PresidentialPardonForm(const std::string& target) :
	AForm("Presidential Pardon Form", 25, 5), m_target(target)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& other) :
	AForm(other), m_target(other.m_target)
{
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other); // Copy the base class parts
		this->m_target = other.m_target;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

// This the actual action that gets triggered if the security checks pass!
void PresidentialPardonForm::performAction() const
{
	std::cout << this->m_target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

