#include "RPN.hpp"
#include <stdexcept>

/**
 * @brief Default constructor.
 *
 * Constructs an RPN object with an empty internal stack,
 * ready to evaluate an expression.
 */
RPN::RPN()
{
}

/**
 * @brief Copy constructor.
 *
 * Creates a new RPN object as a deep copy of an existing one,
 * including the current state of its internal stack.
 *
 * @param other The RPN object to copy from.
 */
RPN::RPN(const RPN &other) : _stack(other._stack)
{
}

/**
 * @brief Copy assignment operator.
 *
 * Assigns the state of one RPN object to another.
 * Guards against self-assignment (e.g. rpn = rpn).
 *
 * @param other The RPN object to assign from.
 * @return A reference to the current object (*this).
 */
RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

/**
 * @brief Destructor.
 *
 * Destroys the RPN object. The internal std::stack
 * cleans up its own memory automatically.
 */
RPN::~RPN()
{
}

/**
 * @brief Checks whether a character is a valid RPN operator.
 *
 * Valid operators are: +, -, *, /
 *
 * @param c The character to check.
 * @return true if the character is a valid operator, false otherwise.
 */
bool RPN::isOperator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

/**
 * @brief Applies a binary operator to two operands.
 *
 * Performs the arithmetic operation defined by @p op on
 * left operand @p a and right operand @p b.
 *
 * Operand order matters for subtraction and division:
 * @p a is always the LEFT operand and @p b is the RIGHT.
 *
 * Example:
 * @code
 *   applyOperator('-', 9, 3); // returns 9 - 3 = 6
 *   applyOperator('/', 8, 2); // returns 8 / 2 = 4
 * @endcode
 *
 * @param op The operator character (+, -, *, /).
 * @param a  The left operand (popped second from the stack).
 * @param b  The right operand (popped first from the stack).
 * @return   The result of applying @p op to @p a and @p b.
 *
 * @throws std::runtime_error if division by zero is attempted.
 * @throws std::runtime_error if an unknown operator is passed.
 */
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

/**
 * @brief Evaluates a Reverse Polish Notation expression.
 *
 * Parses the expression string character by character:
 * - Spaces are skipped.
 * - Digit characters (0-9) are converted to integers and pushed onto the stack.
 * - Operator characters (+, -, *, /) pop the top two values, apply the
 *   operation, and push the result back.
 * - Any other character causes an error.
 *
 * The internal stack is cleared at the start of each call, so the same
 * RPN object can safely evaluate multiple expressions in sequence.
 *
 * Valid expression example:
 * @code
 *   RPN rpn;
 *   rpn.evaluate("5 1 2 + 4 * + 3 -"); // returns 14
 * @endcode
 *
 * Invalid expression examples:
 * @code
 *   rpn.evaluate("+ 3 4");   // Error: operator before any numbers
 *   rpn.evaluate("3 4");     // Error: no operator, two values left on stack
 *   rpn.evaluate("3 4 (*)"); // Error: invalid token '('
 * @endcode
 *
 * @param expression The RPN expression string to evaluate.
 * @return The final computed result as a long long.
 *
 * @throws std::runtime_error if the expression contains invalid tokens.
 * @throws std::runtime_error if an operator is encountered with fewer than
 *         two values on the stack.
 * @throws std::runtime_error if the expression does not reduce to exactly
 *         one value (malformed expression).
 * @throws std::runtime_error if division by zero is attempted.
 */
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
