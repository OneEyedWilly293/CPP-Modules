#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "=== TESTING CORRECT POLYMORPHISM ===" << std::endl;

	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();

	std::cout << "\nTypes:" << std::endl;
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;

	std::cout << "\nSounds:" << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	std::cout << "\nCleaning up..." << std::endl;
	delete meta;
	delete j;
	delete i;

	std::cout << "\n=== TESTING WRONG POLYMORPHISM ===" << std::endl;

	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongI = new WrongCat();

	std::cout << "\nWrong Sounds:" << std::endl;
	wrongI->makeSound();
	wrongMeta->makeSound();

	std::cout << "\nCleaning up..." << std::endl;
	delete wrongMeta;
	delete wrongI;

	return 0;
}
