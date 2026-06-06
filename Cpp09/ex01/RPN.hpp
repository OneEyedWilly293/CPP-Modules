#pragma once

#include <string>
#include <stack>

class RPN
{
	public:
		RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);
		~RPN();

		long long evaluate(const std::string &expression);

	private:
		std::stack<long long> _stack;
		bool isOperator(char c) const;
		long long applyOperator(char op, long long a, long long b) const;
};
