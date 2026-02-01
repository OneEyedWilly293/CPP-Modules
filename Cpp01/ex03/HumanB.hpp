#include "HumanB.hpp"

HumanB::HumanB(const std::string &name) : _name(name), _weapon(nullptr)
{
}

HumanB::~HumanB(void)
{
}

void	HumanB::setWeapon(Weapon &weapon)
{
	_weapon = &weapon;
}

void	HumanB::attack(void) const
{
	if (_weapon == nullptr)
	{
		std::cout << _name << " attacks with their " << "bare hands" << std::endl;
		return ;
	}
	std::cout << _name << "attacks with their " << _weapon->getType() << std::endl;
}
