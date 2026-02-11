
#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed(void) : _raw(0)
{
}

Fixed::Fixed(Fixed const &other) : _raw(other._raw)
{
}

Fixed &Fixed::operator=(Fixed const &other)
{
	if (this != &other)
		this->_raw = other._raw;
	return (*this);
}

Fixed::~Fixed(void)
{
}

Fixed::Fixed(int const n)
{
	/*
		Convert int to fixed:
		value = n
		raw   = n * 256
		We use multiplication (not left shift) to avoid edge cases with negatives.
	*/
	this->_raw = n * (1 << Fixed::_fracBits);
}

Fixed::Fixed(float const n)
{
	/*
		Convert float to fixed:
		raw = roundf(n * 256)
		roundf is allowed by the subject.
	*/
	this->_raw = (int)roundf(n * (float)(1 << Fixed::_fracBits));
}

int Fixed::getRawBits(void) const
{
	return (this->_raw);
}

void Fixed::setRawBits(int const raw)
{
	this->_raw = raw;
}

float Fixed::toFloat(void) const
{
	return ((float)this->_raw / (float)(1 << Fixed::_fracBits));
}

int Fixed::toInt(void) const
{
	/*
		Convert to float then cast to int:
		- easy to understand
		- truncates toward 0 in practice (what you expect for these exercises)
	*/
	return ((int)this->toFloat());
}

/* Comparisons: same scale => compare raw values directly */
bool Fixed::operator>(Fixed const &other) const { return (this->_raw > other._raw); }
bool Fixed::operator<(Fixed const &other) const { return (this->_raw < other._raw); }
bool Fixed::operator>=(Fixed const &other) const { return (this->_raw >= other._raw); }
bool Fixed::operator<=(Fixed const &other) const { return (this->_raw <= other._raw); }
bool Fixed::operator==(Fixed const &other) const { return (this->_raw == other._raw); }
bool Fixed::operator!=(Fixed const &other) const { return (this->_raw != other._raw); }

/*
	Arithmetic:

	Let scale = 256.

	valueA = rawA / scale
	valueB = rawB / scale

	+/-:
		rawResult = rawA +/- rawB

	*:
		valueResult = valueA * valueB
		            = (rawA/scale) * (rawB/scale)
		            = (rawA*rawB) / (scale*scale)
		rawResult   = valueResult * scale
		            = (rawA*rawB) / scale

	/:
		valueResult = valueA / valueB
		            = (rawA/scale) / (rawB/scale)
		            = rawA / rawB
		rawResult   = valueResult * scale
		            = (rawA * scale) / rawB
*/
Fixed Fixed::operator+(Fixed const &other) const
{
	Fixed	res;

	res.setRawBits(this->_raw + other._raw);
	return (res);
}

Fixed Fixed::operator-(Fixed const &other) const
{
	Fixed	res;

	res.setRawBits(this->_raw - other._raw);
	return (res);
}

Fixed Fixed::operator*(Fixed const &other) const
{
	Fixed		res;
	long long	prod;

	prod = (long long)this->_raw * (long long)other._raw;
	res.setRawBits((int)(prod / (1 << Fixed::_fracBits)));
	return (res);
}

Fixed Fixed::operator/(Fixed const &other) const
{
	Fixed		res;
	long long	num;

	/*
		If other._raw == 0, the subject says it's acceptable that it crashes.
		So we do not add a guard here.
	*/
	num = (long long)this->_raw * (long long)(1 << Fixed::_fracBits);
	res.setRawBits((int)(num / (long long)other._raw));
	return (res);
}

/*
	Increment/decrement:

	Smallest representable epsilon is 1 raw unit:
	epsilon = 1 / 256 = 0.00390625
*/
Fixed &Fixed::operator++(void)
{
	this->_raw += 1;
	return (*this);
}

Fixed Fixed::operator++(int)
{
	Fixed	tmp(*this);

	this->_raw += 1;
	return (tmp);
}

Fixed &Fixed::operator--(void)
{
	this->_raw -= 1;
	return (*this);
}

Fixed Fixed::operator--(int)
{
	Fixed	tmp(*this);

	this->_raw -= 1;
	return (tmp);
}

/* min/max: must return references to the original objects */
Fixed &Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed const &Fixed::min(Fixed const &a, Fixed const &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

Fixed const &Fixed::max(Fixed const &a, Fixed const &b)
{
	if (a > b)
		return (a);
	return (b);
}

std::ostream &operator<<(std::ostream &os, Fixed const &fx)
{
	os << fx.toFloat();
	return (os);
}
