#include "Bureaucrat.hpp"
#include "AForm.hpp"

Bureaucrat::Bureaucrat() : m_name("Default"), m_grade(150)
{
}

Bureaucrat::Bureaucrat(const Bureaucrat& other) : m_name(other.m_name), m_grade(other.m_grade)
{
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other)
{
	if (this != &other)
	{
		this->m_grade = other.m_grade;
	}
	return *this;
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : m_name(name), m_grade(grade)
{
	if (m_grade < 1)
	{
		// If grade is smaller than 1(too high), we immediately stop and throw our custom error.
		throw Bureaucrat::GradeTooHighException();
	}
	if (m_grade > 150)
	{
		throw Bureaucrat::GradeTooLowException();
	}
}

std::string Bureaucrat::getName() const
{
	return this->m_name;
}

int Bureaucrat::getGrade() const
{
	return this->m_grade;
}

void Bureaucrat::incrementGrade()
{
	// Guard: Prevent the grade from going to 0 or negative
	if (this->m_grade <= 1)
	{
		throw Bureaucrat::GradeTooHighException();
	}
	this->m_grade--;	// subtract 1 (move closer to grade 1)
}

void Bureaucrat::decrementGrade()
{
	// Guard: Preven the grade from going above 150
	if (this->m_grade >= 150)
	{
		throw Bureaucrat::GradeTooLowException();
	}
	this->m_grade++; // add 1 (move closer to grade 150)
}

// Attemp to sign a AForm
void Bureaucrat::signForm(AForm& AForm)
{
	try
	{
		AForm.beSigned(*this);
		std::cout << this->m_name << " signed " << AForm.getName() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << this->m_name << " couldn't sign " << AForm.getName() << " because "
				  << e.what() << std::endl;
	}
}

void Bureaucrat::executeForm(const AForm& form)
{
	try
	{
		form.execute(*this);
		std::cout << this->m_name << " executed " << form.getName() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << this->m_name << " couldn't execute " << form.getName() << " because "
				  << e.what() << std::endl;
	}
}

// Printing when the exception is caught(return the text)
const char* Bureaucrat::GradeTooHighException::what() const noexcept
{
	return "Bureaucrat grade is too high! (Must be 1 or lower)";
}

const char* Bureaucrat::GradeTooLowException::what() const noexcept
{
	return "Bureaucrat grade is too low! (Must be 150 or higher)";
}

// Teaches the output stream how to print a Bureaucrat object in the exact AFormat required.
std::ostream& operator<<(std::ostream& os, const Bureaucrat& target)
{
	os << target.getName() << ", bureaucrat grade " << target.getGrade() << ".";
	return os;
}
