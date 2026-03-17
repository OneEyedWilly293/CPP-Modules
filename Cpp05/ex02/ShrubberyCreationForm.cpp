#include "ShrubberyCreationForm.hpp"
#include <fstream> // use when working with files

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("Shrubbery Creation Form", 145, 137), m_target("Default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("Shruberry Creation Form", 145, 137), m_target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), m_target(other.m_target)
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	if (this != &other)
	{
		AForm::operator=(other);
		this->m_target = other.m_target;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

void ShrubberyCreationForm::performAction() const
{
	// attach "_shrubbery" to the target's name to make the filename
	std::string filename = this->m_target + "_shrubbery";

	// open an output file stream(ofstream) using that filename
	std::ofstream outfile(filename);

	// check if file opened successfully
	if (!outfile.is_open())
	{
		std::cerr << "Error: Could not open file " << filename << std::endl;
		return;
	}

	// Write ASCII trees directly into the file
	outfile << "       _-_" << std::endl;
	outfile << "    /~~   ~~\\" << std::endl;
	outfile << " /~~         ~~\\" << std::endl;
	outfile << "{               }" << std::endl;
	outfile << " \\  _-     -_  /" << std::endl;
	outfile << "   ~  \\\\ //  ~" << std::endl;
	outfile << "_- -   | | _- _" << std::endl;
	outfile << "  _ -  | |   -_" << std::endl;
	outfile << "      // \\\\" << std::endl;

	// Good practice to close the file when you are done
	outfile.close();
}
