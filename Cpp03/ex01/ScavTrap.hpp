#pragma once

#include "ClapTrap.hpp" // parent's blueprint
#include <iostream>

// The ": public ClapTrap" part means ScavTrap inherits everything from ClapTrap.
class ScavTrap : public ClapTrap
{
	public:
		// OCF
		ScavTrap();
		ScavTrap(const std::string& name);
		ScavTrap(const ScavTrap& other);
		ScavTrap& operator=(const ScavTrap& other);
		~ScavTrap();

	// --- Overridden Function ---
	// We must declare attack() again because ScavTrap attacks differently than Claptrap
	void	attack(const std::string& target);
	void	guardGate(); // New special ability.

};
