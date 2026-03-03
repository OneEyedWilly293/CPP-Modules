#include "ClapTrap.hpp"

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
	std::cout << "=== TEST 1: Normal constructor ===" << std::endl;
	ClapTrap bob("Bob");
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 2: attack, takeDamage, beRepaired ===\n";
	bob.attack("enemy");
	bob.takeDamage(5);
	std::cout << bold_on << "Currently the repair value is +3:\n" << bold_off;
	bob.beRepaired(3);
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 3: Copy constructor ===\n";
	ClapTrap bobCopy(bob);
	bobCopy.attack("target");
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 4: Copy assignment ===\n";
	ClapTrap another("Another");
	another = bob;
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 5: Death scenario - drain all energy ===\n";
	ClapTrap zero("Zero");
	// Zero has 10 energy points, so attack 10 times
	unsigned int i = 0;
	while (i < 11)
	{
		zero.attack("dummy"); // 11th attack should fail
		i++;
	}
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 6: Default Constructor(no name) ===\n";
	// We call the default constructor without any name.
	// It should print "ClapTrap [default] unnamed was constructed!"
	ClapTrap defaultCt;
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 7: Repairing outside limits ===\n";
	ClapTrap Mahito("Mahito");
	/*
	 * PUSHING TO THE ABSOLUTE LIMIT
	 * UINT_MAX represents 4,294,967,295.
	 * Since Bob already has 10 HP, we repair him by (UINT_MAX - 10).
	 * Now, his HP is exactly at the absolute maximum limit.
	 * Energy Points left: 9
	*/
	Mahito.beRepaired(UINT_MAX - 10);
	/*
	 * REPAIRING OUTSIDE THE LIMITS (INTEGER OVERFLOW)
	 * Bob's HP is completely full (4,294,967,295).
	 * If we add 5 more HP, the computer's memory overflows!
	 * Instead of going up, the number wraps around.
	 * His HP will reset and become exactly 4.
	 * Energy Points left: 8
	 */
	Mahito.beRepaired(5);
	std::cout << "\n";

	// =======================================================================

	// The subject says we don't interact with other ClapTraps directly,
	// so we just pass a string as a target. But we can simulate taking damage
	// until we hit 0 HP, and then trying to take MORE damage to see what happens.
	std::cout << "\n=== TEST 8: Attacking times when target HP is 4  ===\n";
	ClapTrap poorGuy("Victim");

	// Starting HP is 10
	poorGuy.takeDamage(2);
	poorGuy.takeDamage(2);
	poorGuy.takeDamage(2);
	poorGuy.takeDamage(2);
	poorGuy.takeDamage(2);
	// Sixth attack: HP is already 0
	poorGuy.takeDamage(2);	// Should say "is already dead"
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 9: Exhausting all Energy Points ===\n";
	ClapTrap spammer("Spammer");

	// Start with 10 energy points. We loop 11 times; the 11th time should fail
	unsigned int	count = 0;
	while (count < 11)
	{
		std::cout << "Action " << count + 1 << ": ";
		spammer.beRepaired(1);
		count++;
	}
	std::cout << "\n";

	// =======================================================================

	std::cout << "\n=== TEST 10: Mixing Attacking and Repairing ===\n";
	ClapTrap fighter("Fighter");

	// Attack 5 times, repair 5 times. Using exactly 10 energy points.
	fighter.attack("Bandit");
    fighter.beRepaired(5);
    fighter.attack("Bandit");
    fighter.beRepaired(5);
    fighter.attack("Bandit");
    fighter.beRepaired(5);
    fighter.attack("Bandit");
    fighter.beRepaired(5);
    fighter.attack("Bandit");
    fighter.beRepaired(5);

	// 11th action should fail because energy is 0
	std::cout << "Final Action: ";
    fighter.attack("Bandit");

	// =======================================================================
	std::cout << "\n--- END OF TESTS (Destructors will run now) ---\n";
	std::cout << bold_on << "\n===== Now I am become Death, the destroyer of worlds =====" << bold_off << std::endl;
	return 0;
}
