#include "Fixed.hpp"

Fixed::Fixed(void) : _rawBits(0)
{
	std::cout << "Default constructor called" << std::endl;
}
Fixed::Fixed(Fixed const &other)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}
Fixed &Fixed::operator=(Fixed const &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_rawBits = other.getRawBits();
	return (*this);
}
Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

/*
 * int constructor:
 * Store n as fixed-point by shifting left by fractional bits (n * 256)
*/
Fixed::Fixed(int const n)
{
	std::cout << "Int constructor called" << std::endl;
	_rawBits = n << _fractionalBits;
}

/*
 * float constructor:
 * Multiply by 256 then round to nearest integer.
 */
Fixed::Fixed(float const f)
{
	std::cout << "Float constructor called" << std::endl;
	const float scale = (float)(1 << _fractionalBits);
	this->_rawBits = (int)roundf(f * scale);
}

int Fixed::getRawBits(void) const
{
	return (this->_rawBits);
}

void Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
}

/*
 * Convert back to float:
 * raw /256.0
 */
float Fixed::toFloat(void) const
{
	const float scale = (float)(1 << _fractionalBits);
	return ((float)this->_rawBits / scale);
}

/*
 * Convert back to int:
 * Truncate toward 0 by discarding fractional bits.
 */
int Fixed::toInt(void) const
{
	return (this->_rawBits >> _fractionalBits);
}

/*
 * Must output floating-points representation.
 */
std::ostream &operator << (std::ostream &os, Fixed const &x)
{
	os << x.toFloat();
	return (os);
}
