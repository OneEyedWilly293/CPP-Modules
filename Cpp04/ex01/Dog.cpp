#include "Dog.hpp"

Dog::Dog()
{
	this->type = "Dog";
	this->brain = new Brain();
	std::cout << "[Dog] Default consturctor called." << std::endl;
}

// DEEP COPY CONSTRUCTOR
Dog::Dog(const Dog& other) : Animal(other)
{
	this->brain = new Brain(*(other.brain));
	std::cout << "[Dog] Copy constructor called (Deep Copy)." << std::endl;
}

// DEEP COPY ASSIGNMENT OPERATOR
Dog& Dog::operator=(const Dog& other)
{
	std::cout << "[Dog] Copy assignment operator called (Deep Copy)." << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*(other.brain));
	}
	return *this;
}

Dog::~Dog()
{
	delete this->brain;
	std::cout << "[Dog] Destructor called." << std::endl;
}

void Dog::makeSound() const
{
	std::cout << "[Dog] Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain() const
{
	return this->brain;
}
