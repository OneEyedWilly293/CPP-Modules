#include "Harl.hpp"

int main(void)
{
	Harl	h;

	h.complain("DEBUG");
	h.complain("INFO");
	h.complain("WARNING");
	h.complain("ERROR");
	h.comlain("NOT_A_LEVEL");
	return (0);
}
