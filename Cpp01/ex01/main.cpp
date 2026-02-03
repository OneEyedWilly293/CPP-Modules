#include "Zombie.hpp"

int main(void)
{
	Zombie *horde;
	int		n;
	int 	i;

	n = 3;
	horde = zombieHorde(n, "HordeFoo");
	if (horde == nullptr)
		return (1);
	i = 0;
	while (i < n)
	{
		horde[i].announce();
		i++;
	}
	delete[] horde;
	return (0);
}
