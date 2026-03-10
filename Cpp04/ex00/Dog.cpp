#include "Dog.hpp"

Dog::Dog()
{
	this->type = "Dog";
	std::cout << "[Dog] Default consturctor called." << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << "[Dog] Copy constructor called." << std::endl;
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << "[Dog] Copy assignment operator called." << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
	}
	return *this;
}

Dog::~Dog()
{
	std::cout << "[Dog] Destructor called." << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "[Dog] Woof! Woof!" << std::endl;
}
