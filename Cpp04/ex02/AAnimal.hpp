#pragma once

#include <iostream>
#include <string>

class AAnimal
{
	protected:
		std::string type;

	public:
		AAnimal();
		AAnimal(const AAnimal& other);
		AAnimal& operator=(const AAnimal& other);

		virtual ~AAnimal();

		virtual void makeSound() const = 0;
		std::string getType() const;
};
