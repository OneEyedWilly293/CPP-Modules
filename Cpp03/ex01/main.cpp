#include "ScavTrap.hpp"

std::ostream& bold_on(std::ostream& os)
{
	return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
	return os << "\e[0m";
}

int main()
{
	std::cout << "\n=== CREATING SCAVTRAP ===\n";
	// Should see ClapTrap's constructor print first, THEN ScavTrap's constructor.
	ScavTrap serena("Serena");
	std::cout << "\n === TESTING INHERITED & NEW ABILITIES ===\n";

	// ScavTrap doesn't have its own takeDamage() or beRepaired() function written in .cpp file.
	// However, because of inheritance, it automatically uses the ones from ClapTrap!
	serena.takeDamage(20);
	serena.beRepaired(10);

	// This should call the specifi ScavTrap attack() we wrote, not the ClapTrap one.
	serena.attack("a poor bandit");

	// Special ability only ScavTrap have.
	serena.guardGate();

	std::cout << "\n=== LIMIT TESTING ===\n";
	ScavTrap foobarbaz("FooBarBaz");
	foobarbaz.takeDamage(120);
	foobarbaz.beRepaired(10);
	foobarbaz.attack("Mr Clap");
	foobarbaz.guardGate();
	std::cout << "\n=== DESTROYING OBJECTS ===\n";
	//Watch the console: ScavTrap's destructor prints FIRST, then ClapTrap's destructor.

	return 0;
}
