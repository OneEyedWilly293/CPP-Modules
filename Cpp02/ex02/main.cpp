#include "Fixed.hpp"
#include <iomanip>

static void	print_title(const char *s)
{
	std::cout << "\n=== " << s << " ===\n";
}

static void	print_bool(const char *label, bool v)
{
	std::cout << label << (v ? "true" : "false") << "\n";
}

int	main(void)
{
	std::cout << std::fixed << std::setprecision(8);

	/* ------------------------------------------------------------ */
	/* 1) Subject's sample test                                     */
	/* ------------------------------------------------------------ */
	print_title("PDF sample");
	{
		Fixed		a;
		Fixed const	b(Fixed(5.05f) * Fixed(2));

		std::cout << a << "\n";
		std::cout << ++a << "\n";
		std::cout << a << "\n";
		std::cout << a++ << "\n";
		std::cout << a << "\n";
		std::cout << b << "\n";
		std::cout << Fixed::max(a, b) << "\n";
	}

	/* ------------------------------------------------------------ */
	/* 2) Comparison operators                                      */
	/* ------------------------------------------------------------ */
	print_title("Comparisons");
	{
		Fixed x(2);
		Fixed y(2);
		Fixed z(3);
		Fixed n(-2);

		std::cout << "x=" << x << " y=" << y << " z=" << z << " n=" << n << "\n";
		print_bool("x == y: ", x == y);
		print_bool("x != y: ", x != y);
		print_bool("x <  z: ", x < z);
		print_bool("z >  x: ", z > x);
		print_bool("x <= y: ", x <= y);
		print_bool("x >= y: ", x >= y);
		print_bool("n <  x: ", n < x);
		print_bool("n <= x: ", n <= x);
		print_bool("n >  x: ", n > x);
	}

	/* ------------------------------------------------------------ */
	/* 3) Arithmetic operators                                      */
	/* ------------------------------------------------------------ */
	print_title("Arithmetic");
	{
		Fixed a(1.50f);
		Fixed b(2.25f);
		Fixed c(-3);

		std::cout << "a=" << a << " b=" << b << " c=" << c << "\n";
		std::cout << "a + b = " << (a + b) << " (expect 3.75)\n";
		std::cout << "b - a = " << (b - a) << " (expect 0.75)\n";
		std::cout << "a * b = " << (a * b) << " (expect 3.375)\n";
		std::cout << "b / a = " << (b / a) << " (expect 1.5)\n";
		std::cout << "c * b = " << (c * b) << " (expect -6.75)\n";
	}

	/* ------------------------------------------------------------ */
	/* 4) Pre/Post ++ and -- (epsilon step)                         */
	/* ------------------------------------------------------------ */
	print_title("Increment / Decrement");
	{
		Fixed t;

		/*
		    epsilon step should be 1/256 = 0.00390625
		    - pre: changes then prints new value
		    - post: prints old value then changes
		*/
		std::cout << "t      = " << t << "\n";
		std::cout << "++t    = " << ++t << "\n";
		std::cout << "t      = " << t << "\n";
		std::cout << "t++    = " << t++ << "\n";
		std::cout << "t      = " << t << "\n";

		std::cout << "--t    = " << --t << "\n";
		std::cout << "t--    = " << t-- << "\n";
		std::cout << "t      = " << t << "\n";
	}

	/* ------------------------------------------------------------ */
	/* 5) min/max (reference return + const overloads)              */
	/* ------------------------------------------------------------ */
	print_title("min/max references");
	{
		Fixed a(10);
		Fixed b(20);

		std::cout << "a=" << a << " b=" << b << "\n";

		/*
		    If min/max return a reference, this will modify the original object.
		*/
		Fixed &m = Fixed::min(a, b);
		m = Fixed(-42);
		std::cout << "After m = -42;  a=" << a << " b=" << b << "\n";

		Fixed &M = Fixed::max(a, b);
		M = Fixed(99);
		std::cout << "After M = 99;   a=" << a << " b=" << b << "\n";

		/*
		    const overloads: should compile and return const references
		*/
		Fixed const ca(1.25f);
		Fixed const cb(1.50f);
		std::cout << "const min(ca, cb) = " << Fixed::min(ca, cb) << "\n";
		std::cout << "const max(ca, cb) = " << Fixed::max(ca, cb) << "\n";
	}

	return (0);
}
