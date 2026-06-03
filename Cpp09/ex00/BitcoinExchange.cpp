#include "BitcoinExchange.hpp"
#include <fstream>		// std::ifstream
#include <sstream>		// std::stringstream
#include <iostream>		// std::cout, std::cerr
#include <stdexcept>	// std::runtime_error
#include <cctype>		// std::isdigit
# include <iomanip>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const std::string &dbFile)
{
	loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDatabase(const std::string &dbFile)
{
	std::ifstream file(dbFile);
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string date;
		std::string rateStr;

		if (std::getline(ss, date, ',' ) && std::getline(ss, rateStr))
			_database[date] = std::stod(rateStr);
	}
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;

	for (size_t i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(date[i]))
			return false;
	}

	int year	= std::stoi(date.substr(0, 4));
	int month	= std::stoi(date.substr(5, 2));
	int day		= std::stoi(date.substr(8, 2));

	if (month < 1 || month > 12)
		return false;

	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Leap year: February gets 29 days
	// A year is a leap year if:
	// - divisible by 4 AND
	// - NOT divisible by 100, UNLESS also divisible by 400
	// Examples: 2000 ✅ 1900 ❌  2024 ✅  2023 ❌
	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	if (isLeapYear)
		daysInMonth[1] = 29;

	if (day < 1 || day > daysInMonth[month - 1])
		return false;
	return true;
}


double BitcoinExchange::getRate(const std::string &date) const
{
	auto it = _database.lower_bound(date);

	if (it != _database.end() && it->first == date)
		return it->second;

	if (it == _database.begin())
		throw std::runtime_error("Error: date out of range.");
	--it;
	return it->second;
}

void BitcoinExchange::processInput(const std::string &inputFile) const
{
	std::ifstream file(inputFile);
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::cout << std::setprecision(10);
	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		size_t pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date		= line.substr(0, pipePos);
		std::string valueStr	= line.substr(pipePos + 1);

		while(!date.empty() && date.back() == ' ')
			date.pop_back();
		while (!date.empty() && date.front() == ' ')
			date = date.substr(1);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		double value;
		try
		{
			size_t pos;
			value = std::stod(valueStr, &pos);

			if (pos != valueStr.size())
				throw std::invalid_argument("invalid");
		}
		catch (...)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		try
		{
			double rate		= getRate(date);
			double result	= value * rate;
			std::cout << date << " => " << value << " = " << result << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
}
