#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"
#include <iostream>
#include <iomanip> /* for std::setw, std::right */

class PhoneBook
{
	private:
		Contact	_contacts[8];
		int		_count;
		int		_nextIndex;

		std::string	_formatField(const std::string &field) const;

	public:
		void add(void);
		void search(void) const;
};

#endif
