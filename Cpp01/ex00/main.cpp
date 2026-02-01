#include "Zombie.hpp"

int main(void)
{
	Zombie *heapZombie = newZombie("HeapFoo");

	heapZombie->announce();
	delete heapZombie;

	randomChump("StackBar");

	{
		Zombie local("LocalBaz");
		local.announce();
	}
	return (0);
}
