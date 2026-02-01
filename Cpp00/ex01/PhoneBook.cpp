#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
	this->_count = 0;
	this->_nextIndex = 0;
}

std::string PhoneBook::_formatField (const std::string &field) const
{
	if (field.length() > 10)
		return (field.substr(0, 9) + ".");
	return (field);
}

void	PhoneBook::add(void)
{
	Contact newContact;

	if (!newContact.setFromInput())
	{
		std::cout << "Input aborted. Contact not added.\n";
		return;
	}
	this->_contacts[this->_nextIndex] = newContact;
	if (this->_count < 8)
		this->_count++;
	this->_nextIndex = (this->_nextIndex + 1) % 8;
	std::cout << "Contact added successfully.\n";
}

void	PhoneBook::search(void) const
{
	std::string	input;
	int			index;
	int			i;

	if (this->_count == 0)
	{
		std::cout << "PhoneBook is empty.\n";
		return;
	}
	std::cout	<< std::right
				<< std::setw(10) << "INDEX" << "|"
				<< std::setw(10) << "FIRST NAME" << "|"
				<< std::setw(10) << "LAST NAME" << "|"
				<< std::setw(10) << "NICKNAME" << "\n";

	i = 0;
	while (i < this->_count)
	{
		std::cout	<< std::setw(10) << i << "|"
					<< std::setw(10) << this->_formatField(this->_contacts[i].getFirstName()) << "|"
					<< std::setw(10) << this->_formatField(this->_contacts[i].getLastName()) << "|"
					<< std::setw(10) << this->_formatField(this->_contacts[i].getNickname()) << "\n";
		i++;
	}
	std::cout << "Enter index of contact to display: ";
	if (!std::getline(std::cin, input))
	{
		std::cout << '\n';
		return;
	}
	if (input.length() != 1 || input[0] < '0' || input[0] > '7')
	{
		std::cout << "Invalid index.\n";
		return;
	}
	index = input[0] - '0';
	if (index < 0 || index >= this->_count)
	{
		std::cout << "Index out of range.\n";
		return;
	}
	std::cout << "First name: " << this->_contacts[index].getFirstName() << "\n";
	std::cout << "Last name: " << this->_contacts[index].getLastName() << "\n";
	std::cout << "Nickname: " << this->_contacts[index].getNickname() << "\n";
	std::cout << "Phone number: " << this->_contacts[index].getPhoneNumber() << "\n";
	std::cout << "Darkest secret: " << this->_contacts[index].getDarkestSecret() << "\n";

}
