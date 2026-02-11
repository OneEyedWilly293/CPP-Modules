#pragma once

#include <iostream>

/*
    ex02 reminder (what we store):
    - _raw is the fixed-point number in "raw units"
    - fractional bits are always 8 (so scale = 2^8 = 256)
    - real value = _raw / 256.0

    This makes comparisons easy (compare _raw),
    and ++/-- easy (add/subtract 1 raw unit = 1/256).
*/

class Fixed
{
	private:
		int					_raw;
		static const int	_fracBits = 8;

	public:
		/* Orthodox Canonical Form */
		Fixed(void);
		Fixed(Fixed const &other);
		Fixed &operator=(Fixed const &other);
		~Fixed(void);

		/* ex01 constructors */
		Fixed(int const n);
		Fixed(float const n);

		/* raw access */
		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		/* conversions */
		float	toFloat(void) const;
		int		toInt(void) const;

		/* ex02: comparisons */
		bool	operator>(Fixed const &other) const;
		bool	operator<(Fixed const &other) const;
		bool	operator>=(Fixed const &other) const;
		bool	operator<=(Fixed const &other) const;
		bool	operator==(Fixed const &other) const;
		bool	operator!=(Fixed const &other) const;

		/* ex02: arithmetic */
		Fixed	operator+(Fixed const &other) const;
		Fixed	operator-(Fixed const &other) const;
		Fixed	operator*(Fixed const &other) const;
		Fixed	operator/(Fixed const &other) const;

		/* ex02: pre/post increment & decrement */
		Fixed	&operator++(void);	/* ++a */
		Fixed	operator++(int);	/* a++ */
		Fixed	&operator--(void);	/* --a */
		Fixed	operator--(int);	/* a-- */

		/* ex02: min/max (both const and non-const overloads) */
		static Fixed		&min(Fixed &a, Fixed &b);
		static Fixed const	&min(Fixed const &a, Fixed const &b);
		static Fixed		&max(Fixed &a, Fixed &b);
		static Fixed const	&max(Fixed const &a, Fixed const &b);
};

/*
    Stream insertion operator:
    - Must not be "friend" (module rule says friend is forbidden unless stated)
    - We can implement it by calling toFloat()
*/
std::ostream	&operator<<(std::ostream &os, Fixed const &fx);
