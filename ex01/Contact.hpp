#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>

class Contact
{
	private:
		/*
			These are privte so only Contact can modify them directly.
		*/
		std::string _first_name;
		std::string _last_name;
		std::string _nickname;
		std::string _phone_number;
		std::string _darkest_secret;

	public:
		/*
			This will ask the user to input all fields.
			It returns:
				- true -> contact successfully filled (no empty fields)
				- false -> input failed (EOF / Ctrl+D), so the caller can stop
		*/
		bool	setFromInput(void);

		/*
			TODO: Getter for alter steps (SEARCH table and full display).
			These are const because they should NOT modify the object.
		*/
		std::string getFirstName(void) const;
		std::string getLastName(void) const;
		std::string getNickname(void) const;
		std::string getPhoneNumber(void) const;
		std::string getDarkestSecret(void) const;
};

#endif
