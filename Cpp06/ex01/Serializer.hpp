#pragma once

#include <cstdint> // for uintptr_t
#include "Data.hpp"

class Serializer
{
	private:
		// OCF: explicitly deleted to prevent instantiation.
		Serializer() = delete;
		Serializer(const Serializer&) = delete;
		Serializer& operator=(const Serializer&) = delete;
		~Serializer() = delete;

	public:
		// Takes a pointer and converts it to the unsigned integer type uintptr_t
		static uintptr_t serialize(Data* ptr);

		// Takes an unsigned integer and converts it abck to a pointer to Data
		static Data* deserialize(uintptr_t raw);

};
