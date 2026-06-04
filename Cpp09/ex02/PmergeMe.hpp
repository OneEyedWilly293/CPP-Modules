#pragma once

#include <vector>
#include <deque>
#include <string>
#include <iostream>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe &other);
		PmergeMe &operator=(const PmergeMe &other);
		~PmergeMe();

		void parseArgs(int argc, char **argv);
		void run();

	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;

		void fjSortVec(std::vector<int> &arr);
		void fjSortDeq(std::deque<int> &arr);

		static std::vector<int> buildInsertionOrder(int pendSize);
};
