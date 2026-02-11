#pragma once

#include <iostream>

class Fixed
{
	private:
		int					_rawBits;
		static const int	_fractionalBits = 8;

	public:
		Fixed(void);
		Fixed(Fixed const &other);
		Fixed &operator=(Fixed const &other);
		~Fixed(void);

		Fixed(int const n);
		Fixed(float const f);

		// accessors
		int		getRawBits(void) const;
		void	setRawBits(int const raw);

		// conversions
		float	toFloat(void) const;
		int		toInt(void) const;
};

// Stream insertion operator: prints floating-point representation.
std::ostream &operator << (std::ostream &os, Fixed const &x);
