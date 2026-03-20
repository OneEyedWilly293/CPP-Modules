#pragma once

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm
{
	private:
		const std::string m_name;
		bool m_isSigned;
		const int m_gradeToSign;
		const int m_gradeToExecute;

	public:
		AForm();
		AForm(const AForm& other);
		AForm& operator=(const AForm& other);
		virtual ~AForm();

		// Custom constructor
		AForm(const std::string& name, int gradeToSign, int gradeToExecute);

		// Getters
		std::string getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;

		void beSigned(const Bureaucrat& bureaucrat);

		// New execution logic
		// public function the Bureaucrat calls. It does the security checks.
		void execute(const Bureaucrat& executor) const;

		// pure virtual functions; Every child class must write their own version of this function.
		virtual void performAction() const = 0;

		// New exception for trying to execute an unsigned AForm
		class NotSignedExeception : public std::exception
		{
			virtual const char* what() const noexcept override;
		};

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

std::ostream& operator<<(std::ostream& os, const AForm& target);

