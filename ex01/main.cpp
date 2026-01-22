#include <iostream>
#include <iomanip>
#include <string>
#include "PhoneBook.hpp"

int main(void)
{
	PhoneBook	phoneBook;
	std::string	cmd;

	while (true)
	{
		std::cout << "Enter command (ADD, SEARCH, EXIT): ";
		if (!std::getline(std::cin, cmd))
		{
			std::cout << "You broke the phonebook :(\n";
			break ;
		}
		if (cmd == "ADD")
			phoneBook.add();
		else if (cmd == "SEARCH")
			phoneBook.search();
		else if (cmd == "EXIT")
			break ;
	}
	return (0);
}
