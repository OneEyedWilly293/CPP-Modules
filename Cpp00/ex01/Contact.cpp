#include "Contact.hpp"

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

	std::cout << "Last name: ";
	if (!std::getline(std::cin,  _last_name))
		return (false);
	while (_last_name.empty())
	{
		std::cout << "Last name cannot be empty. Try again: ";
		if (!std::getline(std::cin, _last_name))
			return (false);
	}

	std::cout << "Nickname: ";
	if (!std::getline(std::cin, _nickname))
		return (false);
	while (_nickname.empty())
	{
		std::cout << "Nickname cannot be empty. Try again: ";
		if (!std::getline(std::cin, _nickname))
			return (false);
	}

	std::cout << "Phone number: ";
	if (!std::getline(std::cin, _phone_number))
		return (false);
	while (_phone_number.empty())
	{
		std::cout << "Phone number cannot be emty. Try again: ";
		if (!std::getline(std::cin, _phone_number))
			return (false);
	}

	std::cout << "Darkest secret: ";
	if (!std::getline(std::cin, _darkest_secret))
		return (false);
	while (_darkest_secret.empty())
	{
		std::cout << "Darkest secret cannot be empty. Try again: ";
		if (!std::getline(std::cin, _darkest_secret))
			return (false);
	}
	return (true);
}

std::string	Contact::getFirstName(void) const { return (_first_name); }
std::string	Contact::getLastName(void) const { return (_last_name); }
std::string	Contact::getNickname(void) const { return (_nickname); }
std::string	Contact::getPhoneNumber(void) const { return (_phone_number); }
std::string	Contact::getDarkestSecret(void) const { return (_darkest_secret); }
