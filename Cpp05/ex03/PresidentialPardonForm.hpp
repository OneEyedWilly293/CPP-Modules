#pragma once

#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
	private:
		// the person being pardoned
		std::string m_target;

	public:
		PresidentialPardonForm();
		PresidentialPardonForm(const PresidentialPardonForm& other);
		PresidentialPardonForm& operator=(const PresidentialPardonForm& other);
		~PresidentialPardonForm();

		// custom constructor that take the target's name
		PresidentialPardonForm(const std::string& target);

		void performAction() const override;
};
