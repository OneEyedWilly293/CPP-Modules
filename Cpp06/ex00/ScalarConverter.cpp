#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>

// actual implementation of the funcion(declared in .hpp)
void ScalarConverter::convert(const std::string& literal)
{
	// --- STEP 1: Identify what the user typed ---
	enum class Type { CHAR, INT, FLOAT, DOUBLE, UNKNOWN };
	auto actual_type = Type::UNKNOWN;

	// Is it a single character? (length of 1, not a number)
	if (literal.length() == 1 && !std::isdigit(literal[0]) && std::isprint(literal[0]))
	{
		actual_type = Type::CHAR;
	}
	// Is it a float? (Contains an 'f' at the end or is a weird math concept like "nanf")
	else if (literal == "-inff" || literal == "+inff" || literal == "nanf" ||
		(literal.find('.') != std::string::npos && literal.back() == 'f'))
	{
		actual_type = Type::FLOAT;
	}
	// Is it a double? (contains a decimal point or is "nan" / "inf")
	else if (literal == "-inf" || literal == "+inf" || literal == "nan" ||
		(literal.find('.') != std::string::npos))
	{
		actual_type = Type::DOUBLE;
	}
	// If it's none of the above, it's a regular integer.
	else
	{
		actual_type = Type::INT;
	}

	// --- STEP 2: Turn the string into a real number ---
	// We will store the final numbe rin a double so it can hold decimals safely.
	double base_value = 0.0;

	try
	{
		if (actual_type == Type::CHAR)
		{
			base_value = static_cast<double>(literal[0]);
		}
		else if (actual_type == Type::INT)
		{
			base_value = static_cast<double>(std::stoi(literal));
		}
		else if (actual_type == Type::FLOAT)
		{
			base_value = static_cast<double>(std::stof(literal));
		}
		else if (actual_type == Type::DOUBLE)
		{
			base_value = std::stod(literal);
		}
	}
	catch(...)
	{
		// If std::stoi or std::stof fail (e.g. word is not a number), print impossible
		std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n";
		return;
	}

	// -- STEP 3: Print the value as all 4 types ---

	// 1. Print as Char
	// Chars can only hold numbers 0 to 127. If it's outside this or a weird math concept, it fails.
	if (std::isnan(base_value) || std::isinf(base_value) || base_value < 0 || base_value > 127)
	{
		std::cout << "char: impossible\n";
	}
	else if (std::isprint(static_cast<char>(base_value)))
	{
		// If it's a printable letter, print it surrounded by quotes
		std::cout << "char: '" << static_cast<char>(base_value) << "'\n";
	}
	else
	{
		std::cout << "char: Non displayable\n";
	}

	// 2. Print as Int
	if (std::isnan(base_value) || std::isinf(base_value) || base_value > std::numeric_limits<int>::max()
		|| base_value < std::numeric_limits<int>::min())
	{
		std::cout << "int: impossible\n";
	}
	else
	{
		std::cout << "int: " << static_cast<int>(base_value) << "\n";
	}

	// 3. Print as Float
	float f = static_cast<float>(base_value);
	// If the float has no decimal values (like 10.0), we force it to print the ".0f"
	if (f == static_cast<int>(f) && !std::isnan(f) && !std::isinf(f))
	{
		std::cout << "float: " << f << ".0f\n";
	}
	else
	{
		std::cout << "float: " << f << "f\n";
	}

	// 4. Print as Double
	double d = static_cast<double>(base_value);
	if (d == static_cast<int>(d) && !std::isnan(d) && !std::isinf(d))
	{
		std::cout << "double: " << d << ".0\n";
	}
	else
	{
		std::cout << "double: " << d << "\n";
	}
}
