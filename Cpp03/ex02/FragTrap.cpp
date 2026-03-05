#include "FragTrap.hpp"

/*
 * DEFAULT CONSTRUCTOR
 * we overwrite the stats with FragTrap's specific values.
 */
FragTrap::FragTrap() : ClapTrap()
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap [default] " << this->_name << " comes alive with a big smile!\n";
}

/*
 * NAME CONSTRUCTOR
 * Passes the name up to ClapTrap, then sets the stats.
 */
FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
{
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap " << this->_name << " comes alive with a big smile!\n";
}

/*
 * COPY CONSTRUCTOR
 * Passes the object up to the ClapTrap copy constructor.
 */
FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
    std::cout << "FragTrap " << this->_name << " was successfully cloned!\n";
}

/*
 * COPY ASSIGNMENT OPERATOR
 * Uses the parent's assignment operator to handle the copying of all shared variables.
 */
FragTrap& FragTrap::operator=(const FragTrap& other)
{
	if (this != &other)
	{
		// Copy the parent attributes
		ClapTrap::operator=(other);
	}
	std::cout << "FragTrap " << this->_name << " has been copy-assigned!\n";
	return *this;
}

/*
 * DESTRUCTOR
 */
FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << this->_name << " explodes into a million happy pieces!\n";
}

/*
 * SPECIAL ABILITY
 */
void FragTrap::highFivesGuys(void)
{
	if (this->_hitPoints == 0)
	{
		std::cout << "FragTrap " << this->_name << " is dead and can't high five...\n";
		return;
	}
	std::cout << "FragTrap " << this->_name << " enthusiastically requests a high-five! ✋\n";
}
