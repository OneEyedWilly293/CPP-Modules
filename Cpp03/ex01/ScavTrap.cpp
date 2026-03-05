#include "ScavTrap.hpp"

/*
 * DEFAULT CONSTRUCTOR
 * The syntax: ": ClapTrap()" explicitly tells c++ to run ClapTrap default constructor FIRST.
 * After the parent is build, we update the states to ScavTrap's specific values.
 */
ScavTrap::ScavTrap() : ClapTrap()
{
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap [default] " << this->_name << " was constructed!\n";
}

/*
 * NAME CONSTRUCTOR
 * We pass the 'name' parameter straight up to the ClapTrap constructor: ": ClapTrap(name):"
 * Then set the 3 new required stats for ScavTrap
 */
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap " << this->_name << " was constructed!\n";
}

/*
 * COPY CONSTRUCTOR
 * We pass the 'other' ScavTrap up to the ClapTrap copy constructor.
 */
ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout << "ScavTrap " << this->_name << " was copy-constructed!\n";
}

/*
 * COPY ASSIGNMENT OPERATOR
 * We can call the parent's assignment operator to handle copying the variables!
 */
ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	if (this != &other)
	{
		// This cleverly calls ClapTrap's '=' operator to copy _name, _hitPoints, etc.
		ClapTrap::operator=(other);
	}
	std::cout << "ScavTrap " << this->_name << " was copy assigned!\n";
	return *this;
}

/*
 * DESTRUCTOR
 */
ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap " << this->_name << " was destroyed!\n";
}

/*
 * OVERRIDDEN ATTACK FUNCTION
 * We write a new attack function so it prints a different message than ClapTrap.
 * It still costs 1 energy and checks for death.
 */
void ScavTrap::attack(const std::string& target)
{
	if (this->_hitPoints == 0)
	{
		std::cout << "ScavTrap " << this->_name << " is dead and cannot attack!\n";
		return;
	}
	if (this->_energyPoints == 0)
	{
		std::cout << "ScavTrap " << this->_name << " has no energy to attack!\n";
		return;
	}

	this->_energyPoints--;
	std::cout << "ScavTrap " << this->_name
			  << " aggressively attacks " << target
			  << ", causing a massive " << this->_attackDamage << " points of damage!\n";
}

/*
 * SPECIAL ABILITY
 * A brand new function that only ScavTraps can use.
 */
void ScavTrap::guardGate()
{
	if (this->_hitPoints == 0)
	{
		std::cout << "ScavTrap " << this->_name << " is dead and cannot guard the gate!\n";
		return;
	}
	std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode!\n";
}
