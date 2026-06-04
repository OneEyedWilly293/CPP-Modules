#include "PmergeMe.hpp"
#include <algorithm>		// std::find, std::lower_bound
#include <chrono>			// std::chrono
#include <stdexcept>		// std::runtime_error
#include <climits>			// INT_MAX
#include <iomanip>			// std::fixed, std::setprecision
#include <cctype>			// std::isdigit

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other) : _vec(other._vec), _deq(other._deq)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::parseArgs(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string s = argv[i];

		for (char c : s)
		{
			if (!std::isdigit(c))
				throw std::runtime_error("Error: invalid input: " + s);
		}
		if (s.empty())
			throw std::runtime_error("Error: empty argument");
		long val = std::stol(s);

		if (val <= 0 || val > INT_MAX)
			throw std::runtime_error("Error: value out of range: " + s);

		_vec.push_back(static_cast<int>(val));
		_deq.push_back(static_cast<int>(val));
	}
	if (_vec.empty())
		throw std::runtime_error("Error: no arguments provided");
}

std::vector<int> PmergeMe::buildInsertionOrder(int pendSize)
{
	std::vector<int> jacob = {0, 1};
	while (jacob.back() < pendSize)
	{
		int n = static_cast<int>(jacob.size());
		jacob.push_back(jacob[n - 1] + 2 * jacob[n - 2]);
	}

	std::vector<int> order;
	for (size_t i = 1; i < jacob.size(); i++)
	{
		int hi = std::min(jacob[i], pendSize);
		int lo = jacob[i - 1];

		for (int k = hi - 1; k >= lo; k--)
		{
			if (k > 0)
				order.push_back(k);
		}
	}
	return order;
}

void PmergeMe::fjSortVec(std::vector<int> &arr)
{
	if (arr.size() <= 1)
		return;

	bool	hasStraggler = (arr.size() % 2 != 0);
	int		straggler = 0;

	if (hasStraggler)
	{
		straggler = arr.back();
		arr.pop_back();
	}

	std::vector<std::pair<int, int>> pairs;
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		int a = arr[i];
		int b = arr[i + 1];
		pairs.push_back(a >= b ? std::make_pair(a, b) : std::make_pair(b, a));
	}

	std::vector<int> mainElems;
	mainElems.reserve(pairs.size());
	for (auto &p : pairs)
		mainElems.push_back(p.first);

	fjSortVec(mainElems);

	std::vector<std::pair<int, int>> sortedPairs;
	sortedPairs.reserve(mainElems.size());
	for (int val : mainElems)
	{
		for (auto &p : pairs)
		{
			if (p.first == val)
			{
				sortedPairs.push_back(p);
				break;
			}
		}
	}
	std::vector<int> pend;
	pend.reserve(sortedPairs.size());
	for (auto &p : sortedPairs)
		pend.push_back(p.second);

	std::vector<int> mainChain = mainElems;
	mainChain.insert (mainChain.begin(), pend[0]);

	std::vector<int> order = buildInsertionOrder(static_cast<int>(pend.size()));
	for (int idx : order)
	{
		auto upper = std::find(mainChain.begin(), mainChain.end(), sortedPairs[idx].first);
		auto insertAt = std::lower_bound(mainChain.begin(), upper, pend[idx]);
		mainChain.insert(insertAt, pend[idx]);
	}
	if (hasStraggler)
	{
		auto insertAt = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(insertAt, straggler);
	}
	arr = mainChain;
}

void PmergeMe::fjSortDeq(std::deque<int> &arr)
{
	if (arr.size() <= 1)
		return;

	bool hasStraggler = (arr.size() % 2 != 0);
	int straggler = 0;
	if (hasStraggler)
	{
		straggler = arr.back();
		arr.pop_back();
	}

	std::deque<std::pair<int, int>> pairs;
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		int a = arr[i];
		int b = arr[i + 1];
		pairs.push_back(a >= b ? std::make_pair(a, b) : std::make_pair(b, a));
	}

	std::deque<int> mainElems;
	for (auto &p : pairs)
		mainElems.push_back(p.first);

	fjSortDeq(mainElems);

	std::deque<std::pair<int, int>> sortedPairs;
	for (int val : mainElems)
	{
		for (auto &p : pairs)
		{
			if (p.first == val)
			{
				sortedPairs.push_back(p);
				break;
			}
		}
	}

	std::deque<int> pend;
	for (auto &p : sortedPairs)
		pend.push_back(p.second);

	std::deque<int> mainChain = mainElems;
	mainChain.push_front(pend[0]);

	std::vector<int> order = buildInsertionOrder(static_cast<int>(pend.size()));
	for (int idx : order)
	{
		auto upper = std::find(mainChain.begin(), mainChain.end(), sortedPairs[idx].first);
		auto insertAt = std::lower_bound(mainChain.begin(), upper, pend[idx]);
		mainChain.insert(insertAt, pend[idx]);
	}

	if (hasStraggler)
	{
		auto insertAt = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
		mainChain.insert(insertAt, straggler);
	}
	arr = mainChain;
}

void PmergeMe::run()
{
	std::cout << "Before:";
	for (int x : _vec)
		std::cout << " " << x;
	std::cout << "\n";

	auto t1 = std::chrono::high_resolution_clock::now();
	fjSortVec(_vec);
	auto t2 = std::chrono::high_resolution_clock::now();

	double vecTime = std::chrono::duration<double, std::micro>(t2 - t1).count();

	auto t3 = std::chrono::high_resolution_clock::now();
	fjSortDeq(_deq);
	auto t4 = std::chrono::high_resolution_clock::now();

	double deqTime = std::chrono::duration<double, std::micro>(t4 - t3).count();

	std::cout << "After: ";
	for (int x : _vec)
		std::cout << " " << x;
	std::cout << "\n";

	std::cout << std::fixed << std::setprecision(5);
	std::cout << "Time to process a range of " << _vec.size()
			   << " elements with std::vector : " << vecTime << " us\n";
	std::cout << "Time to process a range of " << _deq.size()
			   << " elements with std::deque : " << deqTime << " us\n";
}

