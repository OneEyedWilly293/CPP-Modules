#include "Contact.hpp"
#include <iostream>

/*
	Helper idea:
	We read a full line using std::getline (handles spaces).
	std::getline returns a stream reference that can be checked in an if:
	- if it fails (EOF/error), we return false to the caller.
*/
bool	Contact::setFromInput(void)
{
	std::cout << "First name: ";
	if (!std::getline(std::cin, _first_name))
		return (false);
	while (_first_name.empty())
	{
		std::cout << "First name cannot be empty. Try again: ";
		if (!std::getline(std::cin, _first_name))
			return (false);
	}
}
