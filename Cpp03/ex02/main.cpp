#include "FragTrap.hpp"

int main()
{
	std::cout << "\n=== CREATING FRAGTRAP ===\n";
	FragTrap frodo("Frodo");

	std::cout << "\n=== TESTING FRAGTRAP ABILITIES ===\n";
	// This uses the default attack() from ClapTrap, doing 30 damage!
	frodo.attack("Sauron");

	// Uses inherited takeDamage and beRepaired
	frodo.takeDamage(50);
	frodo.beRepaired(50);

	// FragTrap's unique ability
	frodo.highFivesGuys();

	std::cout << "\n=== DESTROYING OBJECTS ===\n";
	return 0;
}
