#pragma once

#include <stack>
#include <deque>

/*
 * The second template parameter "Container"
 * It defaults to std::deque<T>, which is what std::stack uses internally anyway
 * But now we can refer to it directly by name(makes the code shorter).
 */
template <typename T, typename Container = std::deque<T>>
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
		// We named our the container "Container", the typedef is now clean and short
		// (vs) Compare this to: std::stack<T>::container_type::iterator <- verbose!
		typedef typename Container::iterator				iterator;
		typedef typename Container::const_iterator			const_iterator;
		typedef typename Container::reverse_iterator		reverse_iterator;
		typedef typename Container::const_reverse_iterator	const_reverse_iterator;

		// Forward iterators
		iterator		begin()			{ return (this->c.begin()); }
		iterator		end()			{ return (this->c.end()); }
		const_iterator	begin() const	{ return (this->c.begin()); }
		const_iterator	end() const		{ return (this->c.end()); }

		// Reverse iterators(optional)
		reverse_iterator		rbegin()		{ return (this->c.begin()); }
		reverse_iterator		rend()			{ return (this->c.rend()); }
		const_reverse_iterator	rbegin() const	{ return (this->c.rbegin()); }
		const_reverse_iterator	rend() const	{ return (this->c.rend()); }
};
