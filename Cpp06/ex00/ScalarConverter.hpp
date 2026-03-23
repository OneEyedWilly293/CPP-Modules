#pragma once

#include <string>

class ScalarConverter
{
	private:
		// class must NOT be instantiable (we can't create objects from it).
		// C++20's '= delete' to strictly forbid the creation and copying of ojects.
		ScalarConverter() = delete;
		ScalarConverter(const ScalarConverter&) = delete;
		ScalarConverter& operator=(const ScalarConverter&) = delete;
		~ScalarConverter() = delete;

	public:
		// 'static' means we dont need to create an object to use this function
		// can just call it directly like this: ScalarConverter::convert("42")
		static void convert(const std::string& literal);
};
