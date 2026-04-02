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
		// Default constructor
		// called when you create and Array without specifying a size.
		Array() : _elements(nullptr), _size(0)
		{
			std::cout << "Array default constructor called" << std::endl;
		}

		// Parameterized constructor
		// called when you create and Array and give it a size.
		// 'new T[_size]()' asks the OS to give us enough memory to hold '_size' number of 'T' elements.
		// The empty parenthesis '()' ensures that built-in types(like int or float) are
		// initialized to 0 by default
		Array(unsigned int n) : _size(n)
		{
			_elements = new T[_size]();
			std::cout << "Array parameterized constructor called (size " << _size
				<< ")" << std::endl;
		}

		// Copy constructor (when crate a new Array as a copy of an existing one)
		// we allocate NEW memory for this new array(Deep Copy).
		Array(const Array& other) : _size(other._size)
		{
			std::cout << "Array copy constructor called" << std::endl;
			_elements = new T[_size]();
			for (unsigned int i = 0; i < _size; i++)
			{
				_elements[i] = other._elements[i];
			}
		}

		// Assignment operator (when use the '=' sign to assign an already-existing array to another already-existing array).
		// e.g. arr2 = arr1;
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

		// Destructor
		~Array()
		{
			std::cout << "Array destructor called" << std::endl;
			delete[] _elements;
		}

	// Custom Exception class
	class OutOfBoundsException : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return "Index is out of bounds!";
			}
	};

	// SUBSCRIPT OPERATOR (Read/Write)
	// Allows us to access elements like array[i].(square brackets to access elements, like 'arr[0]').
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
	// if our array is marked 'const', c++ will call this version instead.
	// Returns a const reference (const T&) to prevent modification.
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
