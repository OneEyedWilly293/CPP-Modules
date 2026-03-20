#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : m_name("Default Form"), m_isSigned(false), m_gradeToSign(150), m_gradeToExecute(150)
{
}

Form::Form(const Form& other) : m_name(other.m_name), m_isSigned(other.m_isSigned), m_gradeToSign(other.m_gradeToSign), m_gradeToExecute(other.m_gradeToExecute)
{
}

Form& Form::operator=(const Form& other)
{
	if (this != &other)
	{
		// We can ONLY copy the boolean, the other variables are locked as 'const'.
		this->m_isSigned = other.m_isSigned;
	}
	return *this;
}

Form::~Form()
{
}

// CUSTOM CONSTRUCTOR: we validate the grades exactly like we did for the Bureaucrat.
Form::Form(const std::string& name, int gradeToSign, int gradeToExecute) : m_name(name),
		m_isSigned(false), m_gradeToSign(gradeToSign), m_gradeToExecute(gradeToExecute)
{
	// Check the signing grade
	if (m_gradeToSign < 1)
	{
		throw Form::GradeTooHighException();
	}
	if (m_gradeToSign > 150)
	{
		throw Form::GradeTooLowException();
	}

	// Check the execution grade
	if (m_gradeToExecute < 1)
	{
		throw Form::GradeTooHighException();
	}
	if (m_gradeToExecute > 150)
	{
		throw Form::GradeTooLowException();
	}
}

std::string Form::getName() const
{
	return this->m_name;
}

bool Form::getIsSigned() const
{
	return this->m_isSigned;
}

int Form::getGradeToSign() const
{
	return this->m_gradeToSign;
}

int Form::getGradeToExecute() const
{
	return this->m_gradeToExecute;
}

// SIGNING LOGIC
void Form::beSigned(const Bureaucrat& bureaucrat)
{
	// 20.03 Robust check: Check if the form is already signed!
	if (this->m_isSigned)
	{
		throw std::runtime_error("Form is already signed!");
	}
	// Since: Grade 1 is the highest. Grade 150 is the lowest.
	// if the Bureaucrat's grade is a larger number than the required grade, it means
	// they are too low-ranking to sign it
	if (bureaucrat.getGrade() > this->m_gradeToSign)
	{
		throw Form::GradeTooLowException();
	}
	// if they make it past the exception check, they are worthy!
	this->m_isSigned = true;
}

const char* Form::GradeTooHighException::what() const noexcept
{
	return "Error: Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const noexcept
{
	return "Error: Form grade is too low!";
}

std::ostream& operator<<(std::ostream& os, const Form& target)
{
	os	<< "Form: " << target.getName()
		<< " | Signed: " << (target.getIsSigned() ? "Yes" : "No")
		<< " | Grade to Sign: " << target.getGradeToSign()
		<< " | Grade to Execute: " << target.getGradeToExecute();
	return os;
}
