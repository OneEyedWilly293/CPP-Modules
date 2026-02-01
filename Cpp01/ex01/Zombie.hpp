#pragma once

#include <iostream>
#include <string>

class Zombie
{
	private:
		std::string _name;

	public:
		Zombie(void);
		Zombie(const std::string &name);
		~Zombie(void);

		void	announce(void) const;
		void	setName(const std::string &name);
};

Zombie *zombieHorde(int N, std::string name);

