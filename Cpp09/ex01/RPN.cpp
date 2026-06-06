#include "RPN.hpp"
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const RPN &other) : _stack(other._stack)
{
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN()
{
}

bool RPN::isOperator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

long long RPN::applyOperator(char op, long long a, long long b) const
{
	if (op == '+')
		return a + b;
	if (op == '-')
		return a - b;
	if (op == '*')
		return a * b;
	if (op == '/')
	{
		if (b == 0)
			throw std::runtime_error("Error: division by zero");
		return a / b;
	}
	throw std::runtime_error("Error: unknown operator");
}

long long RPN::evaluate(const std::string &expression)
{
	while (!_stack.empty())
		_stack.pop();

	for (auto token : expression)
	{
		if (token == ' ')
			continue;

		if (std::isdigit(token))
		{
			_stack.push(token - '0');
		}
		else if (isOperator(token))
		{
			if (_stack.size() < 2)
				throw std::runtime_error("Error: invalid expression");

			long long b = _stack.top();
			_stack.pop();

			long long a = _stack.top();
			_stack.pop();

			_stack.push(applyOperator(token, a, b));
		}
		else
		{
			throw std::runtime_error("Error: invalid token in expression");
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error: invalid expression");

	return _stack.top();
}
