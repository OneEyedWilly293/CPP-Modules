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

		void announce(void) const;
		void setName(const std::string &name);
};

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);
