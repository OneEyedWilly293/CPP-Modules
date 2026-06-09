#include "BitcoinExchange.hpp"
#include <fstream>		// std::ifstream
#include <sstream>		// std::stringstream
#include <iostream>		// std::cout, std::cerr
#include <stdexcept>	// std::runtime_error
#include <cctype>		// std::isdigit
#include <chrono>		// std::chrono
#include <iomanip>

/**
 * @brief  Default constructor.
 *
 * Initialises an empty BitcoinExchange object with no database loaded.
 * Use the parameterised constructor or loadDatabase() to populate it.
 */
BitcoinExchange::BitcoinExchange()
{
}

/**
 * @brief  Parameterised constructor — loads the database immediately.
 *
 * Opens the given CSV file and populates the internal _database map.
 * The CSV must follow the format: "date,exchange_rate" with a header line.
 *
 * @param  dbFile  Path to the CSV database file (e.g. "data.csv").
 * @throws std::runtime_error if the file cannot be opened.
 *
 * @example
 * @code
 *   BitcoinExchange btc("data.csv");
 * @endcode
 */
BitcoinExchange::BitcoinExchange(const std::string &dbFile)
{
	loadDatabase(dbFile);
}

/**
 * @brief  Copy constructor.
 *
 * Creates a new BitcoinExchange object as a deep copy of another.
 * The internal _database map is fully copied.
 *
 * @param  other  The BitcoinExchange object to copy from.
 */
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _database(other._database)
{
}

/**
 * @brief  Copy assignment operator.
 *
 * Assigns the contents of another BitcoinExchange object to this one.
 * Guards against self-assignment before copying.
 *
 * @param  other  The BitcoinExchange object to assign from.
 * @return Reference to this object.
 */
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_database = other._database;
	return *this;
}

/**
 * @brief  Destructor.
 *
 * std::map manages its own memory — no manual cleanup needed.
 */
BitcoinExchange::~BitcoinExchange()
{
}

/**
 * @brief  Loads Bitcoin exchange rate data from a CSV file into _database.
 *
 * Reads the file line by line, skipping the header row. Each subsequent
 * line is expected to be in the format "YYYY-MM-DD,rate". Valid entries
 * are inserted into _database as key-value pairs.
 *
 * Since std::map sorts by key automatically, and dates are in YYYY-MM-DD
 * format, the map will be sorted chronologically after loading.
 *
 * @param  dbFile  Path to the CSV file to load.
 * @throws std::runtime_error if the file cannot be opened.
 *
 * @note   Lines that cannot be split on ',' are silently skipped.
 */
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

/**
 * @brief  Validates whether a date string represents a real calendar date.
 *
 * Performs the following checks in order:
 *  1. String length must be exactly 10 characters.
 *  2. Characters at index 4 and 7 must be '-'.
 *  3. All other characters must be digits.
 *  4. Constructs a std::chrono::year_month_day and calls .ok() to verify
 *     the date is a real calendar date (correct days per month, leap years).
 *
 * @param  date  The date string to validate (expected: "YYYY-MM-DD").
 * @return true if the date is a valid calendar date, false otherwise.
 *
 * @example
 * @code
 *   isValidDate("2024-02-29") // true  (2024 is a leap year)
 *   isValidDate("2023-02-29") // false (2023 is not a leap year)
 *   isValidDate("2024-04-31") // false (April has 30 days)
 *   isValidDate("2001-42-42") // false (month 42 doesn't exist)
 * @endcode
 */
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

	std::chrono::year_month_day ymd {
		std::chrono::year{year},
		std::chrono::month{static_cast<unsigned>(month)},
		std::chrono::day{static_cast<unsigned>(day)}
	};

	return ymd.ok();
}

/**
 * @brief  Retrieves the Bitcoin exchange rate for the closest lower or equal date.
 *
 * Uses std::map::lower_bound() which returns an iterator to the first
 * element whose key is >= the given date.
 *
 * Logic:
 *  - If the iterator points to an exact match, return that rate directly.
 *  - If the iterator points to a greater date (no exact match), step back
 *    one position (--it) to get the closest lower date.
 *  - If the iterator is at begin() with no exact match, no valid date
 *    exists in the database before the given date — throw an error.
 *
 * @param  date  The target date string in "YYYY-MM-DD" format.
 * @return The exchange rate (double) for the closest matching date.
 * @throws std::runtime_error if no date in the database is <= the given date.
 *
 * @example
 * @code
 *   // Database has "2011-01-01" and "2011-01-04" but not "2011-01-03"
 *   getRate("2011-01-03") // returns rate for "2011-01-01"
 *   getRate("2011-01-04") // returns rate for "2011-01-04" (exact match)
 * @endcode
 */
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

/**
 * @brief  Reads an input file and prints the Bitcoin value for each entry.
 *
 * Opens the input file and processes it line by line, skipping the header.
 * For each line the following pipeline runs:
 *  1. Find the '|' separator — if missing, print "Error: bad input".
 *  2. Trim whitespace from the date and value substrings.
 *  3. Validate the date with isValidDate() — if invalid, print "Error: bad input".
 *  4. Parse the value with std::stod() — if not a number, print "Error: bad input".
 *  5. Check value range (0 to 1000) — print appropriate error if out of range.
 *  6. Look up the exchange rate with getRate() and print the result.
 *
 * Output format: "YYYY-MM-DD => value = result"
 *
 * @param  inputFile  Path to the input file to process.
 *
 * @note   Errors on individual lines do not stop processing —
 *         the program continues to the next line after each error.
 *
 * @example
 * @code
 *   // Input line:  "2011-01-03 | 3"
 *   // Output:      "2011-01-03 => 3 = 0.9"
 *
 *   // Input line:  "2012-01-11 | -1"
 *   // Output:      "Error: not a positive number."
 *
 *   // Input line:  "2001-42-42 | 1"
 *   // Output:      "Error: bad input => 2001-42-42"
 * @endcode
 */
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
