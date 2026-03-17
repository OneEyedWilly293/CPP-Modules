#pragma once

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class Form
{
	private:
		const std::string m_name;
		bool m_isSigned;
		const int m_gradeToSign;
		const int m_gradeToExecute;

	public:
		Form();
		Form(const Form& other);
		Form& operator=(const Form& other);
		~Form();

		// Custom constructor
		Form(const std::string& name, int gradeToSign, int gradeToExecute);

		// Getters
		std::string getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		// THE CORE LOGIC
		// this function takes a Bureaucrat and decides if they are worthy of signing.
		void beSigned(const Bureaucrat& bureaucrat);

		// custom exceptions
		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const noexcept override;
		};

		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const noexcept override;
		};
};

// Operator overload to print the Form's details.
std::ostream& operator<<(std::ostream& os, const Form& target);
