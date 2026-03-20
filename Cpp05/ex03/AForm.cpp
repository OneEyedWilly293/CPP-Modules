#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : m_name("Default AForm"), m_isSigned(false), m_gradeToSign(150), m_gradeToExecute(150)
{
}

AForm::AForm(const AForm& other) : m_name(other.m_name), m_isSigned(other.m_isSigned), m_gradeToSign(other.m_gradeToSign), m_gradeToExecute(other.m_gradeToExecute)
{
}

AForm& AForm::operator=(const AForm& other)
{
	if (this != &other)
	{
		// We can ONLY copy the boolean, the other variables are locked as 'const'.
		this->m_isSigned = other.m_isSigned;
	}
	return *this;
}

AForm::~AForm()
{
}

// CUSTOM CONSTRUCTOR: we validate the grades exactly like we did for the Bureaucrat.
AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute) : m_name(name),
		m_isSigned(false), m_gradeToSign(gradeToSign), m_gradeToExecute(gradeToExecute)
{
	// Check the signing grade
	if (m_gradeToSign < 1)
	{
		throw AForm::GradeTooHighException();
	}
	if (m_gradeToSign > 150)
	{
		throw AForm::GradeTooLowException();
	}

	// Check the execution grade
	if (m_gradeToExecute < 1)
	{
		throw AForm::GradeTooHighException();
	}
	if (m_gradeToExecute > 150)
	{
		throw AForm::GradeTooLowException();
	}
}

std::string AForm::getName() const
{
	return this->m_name;
}

bool AForm::getIsSigned() const
{
	return this->m_isSigned;
}

int AForm::getGradeToSign() const
{
	return this->m_gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return this->m_gradeToExecute;
}

// SIGNING LOGIC
void AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (this->m_isSigned)
	{
		throw std::runtime_error("Form is already signed!");
	}
	// Since: Grade 1 is the highest. Grade 150 is the lowest.
	// if the Bureaucrat's grade is a larger number than the required grade, it means
	// they are too low-ranking to sign it
	if (bureaucrat.getGrade() > this->m_gradeToSign)
	{
		throw AForm::GradeTooLowException();
	}
	// if they make it past the exception check, they are worthy!
	this->m_isSigned = true;
}

const char* AForm::GradeTooHighException::what() const noexcept
{
	return "Error: AForm grade is too high!";
}

const char* AForm::GradeTooLowException::what() const noexcept
{
	return "Error: AForm grade is too low!";
}

void AForm::execute(const Bureaucrat& executor) const
{
	// Check if the form is actually signed
	if (!this->m_isSigned)
	{
		throw AForm::NotSignedExeception();
	}
	// Check if the Bureaucrat is high-ranking enough to execute it
	if (executor.getGrade() > this->m_gradeToExecute)
	{
		throw AForm::GradeTooLowException();
	}
	// if both check passes, trigger the specific action of the child class
	this->performAction();
}

const char* AForm::NotSignedExeception::what() const noexcept
{
	return "Error: Form cannot be executed because it is not signed!";
}

std::ostream& operator<<(std::ostream& os, const AForm& target)
{
	os	<< "AForm: " << target.getName()
		<< " | Signed: " << (target.getIsSigned() ? "Yes" : "No")
		<< " | Grade to Sign: " << target.getGradeToSign()
		<< " | Grade to Execute: " << target.getGradeToExecute();
	return os;
}
