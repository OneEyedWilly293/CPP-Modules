#pragma once

#include <iostream>
#include <exception>

template <typename T>
class Array
{
	private:
		T*				_elements;
		unsigned int	_size;

	public:
		Array() : _elements(nullptr), _size(0)
		{
			std::cout << "Array default constructor called" << std::endl;
		}

		Array(unsigned int n) : _size(n)
		{
			_elements = new T[_size]();
			std::cout << "Array parameterized constructor called (size " << _size
				<< ")" << std::endl;
		}

		Array(const Array& other) : _size(other._size)
		{
			std::cout << "Array copy constructor called" << std::endl;
			_elements = new T[_size]();
			for (unsigned int i = 0; i < _size; i++)
			{
				_elements[i] = other._elements[i];
			}
		}

		Array& operator=(const Array& other)
		{
			std::cout << "Array assignment operator called" << std::endl;
			if (this != &other)
			{
				delete[] _elements;
				_size = other._size;
				_elements = new T[_size]();
				for (unsigned int i = 0; i < _size; i++)
				{
					_elements[i] = other._elements[i];
				}
			}
			return *this;
		}

		~Array()
		{
			std::cout << "Array destructor called" << std::endl;
			delete[] _elements;
		}

	class OutOfBoundsException : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return "Index is out of bounds!";
			}
	};

	// SUBSCRIPT OPERATOR (Read/Write)
	// Allows us to access elements like array[i].
	// We throw our custom exception if the index is invalid.
	// Returns a reference (T&) so we can modify the element.
	T& operator[](unsigned int index)
	{
		if (index >= _size)
			throw OutOfBoundsException();
		return _elements[index];
	}

	// SUBSCRIPT OPERATOR (Read-Only)
	// We need a const version of the operator for const arrays.
	// Returns a const reference (const T&) to preven modification.
	const T& operator[](unsigned int index) const
	{
		if (index >= _size)
			throw OutOfBoundsException();
		return _elements[index];
	}

	// SIZE FUNCTION
	// Returns the number of elements. It is marked 'const'
	// because calling size() should never modify the array.
	unsigned int size() const
	{
		return _size;
	}
};
