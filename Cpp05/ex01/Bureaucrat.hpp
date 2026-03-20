#pragma once

#include <iostream>
#include <string>
#include <exception>

class Form;

class Bureaucrat
{
	private:
		const	std::string m_name;
		int		m_grade;

	public:
		Bureaucrat();
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat& operator=(const Bureaucrat& other);
		~Bureaucrat();

		//Custom constructor
		Bureaucrat(const std::string& m_name, int m_grade);

		//getters(accessors)
		std::string	getName() const;
		int	getGrade() const;

		// Promotes the bureaucrat. Since 1 is the highest grade, incrementing
		// means subtracting 1.
		void	incrementGrade();

		// Demotes the bureaucrat. Adding 1 to the grade.
		void	decrementGrade();

		void	signAForm(Form& Form);

		// Exceptions (custom errors)
		// These custom error classes inherit from the standard C++ exception class.
		class GradeTooHighException : public std::exception
		{
			public:
				// 'what()' is a standard C++ function that returns the error message text.
				// 'noexcept' means this error-reporting function is guaranteed not to crash/throw errors itself.
				virtual const char* what() const noexcept override;
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const noexcept override;
		};
};

// OPERATOR OVERLOADING
// This teaches the std::cout stream how to print our custom object.
std::ostream& operator<<(std::ostream& os, const Bureaucrat& target);
