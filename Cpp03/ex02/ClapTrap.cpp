#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("unamed"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap [default] " << _name << " was constructed!\n";
}


ClapTrap::ClapTrap(const std::string& name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << _name << " was constructed!\n";
}

ClapTrap::ClapTrap(const ClapTrap& other)
	:	_name(other._name),
		_hitPoints(other._hitPoints),
		_energyPoints(other._energyPoints),
		_attackDamage(other._attackDamage)
{
	std::cout << "ClapTrap " << _name << " was copy-constructed!\n";
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	if (this != &other)
	{
		_name			= other._name;
		_hitPoints		= other._hitPoints;
		_energyPoints	= other._energyPoints;
		_attackDamage	= other._attackDamage;
	}
	std::cout << "ClapTrap " << _name << " was copy-assigned!\n";
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap " << _name << " was destroyed\n";
}

void	ClapTrap::attack(const std::string& target)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " is dead and cannot attack!\n";
		return;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " has no energy to attack!\n";
		return;
	}
	_energyPoints--;
	std::cout << "ClapTrap " << _name
			  << " attacks " << target
			  << ", causing " << _attackDamage << " points of damage!\n";
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " is already dead!\n";
		return;
	}
	if (amount >= _hitPoints)
		_hitPoints = 0;
	else
		_hitPoints -= amount;
	std::cout << "ClapTrap " << _name << " takes " << amount << " damage! HP: "
			<< _hitPoints << "\n";
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " is dead and cannot repair!\n";
		return;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " has no energy to repair!\n";
		return;
	}
	_energyPoints--;
	_hitPoints += amount;
	std::cout << "ClapTrap " << _name << " repairs itself for "
				<< "Hp! Hp: " << _hitPoints << "\n";
}
