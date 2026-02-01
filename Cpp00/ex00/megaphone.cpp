#include <iostream>
#include <cctype>

int	main(int argc, char **argv)
{
	int	i = 1;
	int	j;

	if (argc < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
		return (0);
	}
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(argv[i][j])));
			j++;
		}
		i++;
	}
	std::cout << "\n";
	return (0);
}
