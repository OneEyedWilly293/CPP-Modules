#pragma once

#include <map>		// std::map
#include <string>	// std::string

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		// Constructor that loads the DB CSV
		BitcoinExchange(const std::string &dbFile);

		// reads the input file and prints results
		void processInput(const std::string &inputFile) const;

	private:
		std::map<std::string, double> _database;

		// loads data(csv) into _database
		void loadDatabase(const std::string &dbFile);

		// Checker: if a date string is valid(correct format: YYYYMMDD)
		bool isValidDate(const std::string &date) const;

		// Find the closest lower-or-equal date in _database and returns its rate
		double getRate(const std::string &date) const;
};
