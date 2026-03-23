#include "Serializer.hpp"

// serialize(): we use reinterpret_cast to take the memory address where 'ptr'
// is pointing and store it as a raw, unsigned integer (uintptr_t).
uintptr_t Serializer::serialize(Data* ptr)
{
	auto raw_address = reinterpret_cast<uintptr_t>(ptr);
	return raw_address;
}

// deserialize(): we use reinterpret_cast to take the raw integer 'raw' and tell
// the compiler to treat it as a memory address pointing to a Data object (Data*).
Data* Serializer::deserialize(uintptr_t raw)
{
	auto data_pointer = reinterpret_cast<Data*>(raw);
	return data_pointer;
}
