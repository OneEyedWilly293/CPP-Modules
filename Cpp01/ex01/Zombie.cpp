#include "Zombie.hpp"

Zombie::Zombie(void) : _name("Unnamed")
{
}

Zombie::Zombie(const std::string &name) : _name(name)
{
}

Zombie::~Zombie(void)
{
	std::cout << _name << " is destroyed" << std::endl;
}

void Zombie::setName(const std::string &name)
{
	_name = name;
}

void Zombie::announce(void) const
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
