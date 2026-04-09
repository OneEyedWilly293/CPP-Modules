#pragma once

#include <stack>	// std::stack - the class we inherit from
#include <deque>	// std::deque - the default underlying container

/*
 * The second template parameter "Container"
 * It defaults to std::deque<T>, which is what std::stack uses internally anyway
 * But now we can refer to it directly by name(makes the code shorter).
 * template parameters:
 * @T -> the type of data stored
 * @Container -> the internal storage container(defaults to std::deque<T>)
 */
template <typename T, typename Container = std::deque<T>>
// We inthere from std::stack
// Therefore MutantStack automatically has push(), pop(), top(), size(), empty()...
// We only ADD iterator support on top of that
class MutantStack : public std::stack<T, Container>
{
	public:
		// OCF
		MutantStack() : std::stack<T, Container>() {}
		MutantStack(const MutantStack& other) : std::stack<T, Container>(other) {}
		MutantStack& operator=(const MutantStack& other)
		{
			if (this != &other)
				std::stack<T, Container>::operator=(other);
			return (*this);
		}
		~MutantStack() {}

		// Iterators
		// We named our the container "Container", the typedef is now clean and short(we create short aliases)
		// (vs) Compare this to: std::stack<T>::container_type::iterator <- verbose!
		typedef typename Container::iterator				iterator;
		typedef typename Container::const_iterator			const_iterator;
		typedef typename Container::reverse_iterator		reverse_iterator;
		typedef typename Container::const_reverse_iterator	const_reverse_iterator;

		// Forward iterators methods
		// "this->c" is the protected member inside std::stack
		// It IS the underlying std::dqeue that actually stores the data
		// By calling c.begin() and c.end(), we expose iteration over it
		iterator		begin()			{ return (this->c.begin()); } //begin() -> points to the BOTTOM of the stack(first element pushed)
		iterator		end()			{ return (this->c.end()); }	// end() -> points one past the TOP of the stack
		const_iterator	begin() const	{ return (this->c.begin()); }
		const_iterator	end() const		{ return (this->c.end()); }

		// Reverse iterators(optional)
		reverse_iterator		rbegin()		{ return (this->c.rbegin()); }
		reverse_iterator		rend()			{ return (this->c.rend()); }
		const_reverse_iterator	rbegin() const	{ return (this->c.rbegin()); }
		const_reverse_iterator	rend() const	{ return (this->c.rend()); }
};
