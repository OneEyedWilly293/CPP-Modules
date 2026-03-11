#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
	//UNCOMMENTING THE LINE BELOW WILL CAUSE A COMPILER ERROR!
	// AAnimal* test = new AAnimal();
	//Error: cannot allocate an object of abstract type 'AAnimal'

	// However, we can STILL use AAnimal pointers to hold drived objects!
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();

	std::cout << "\nTypes:" <<std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	std::cout << "\nSounds:" << std::endl;
	i->makeSound();
	j->makeSound();

	std::cout << "\nCleaning up..." << std::endl;
	delete j;
	delete i;

	return 0;
}
