#include <iostream>
#include <fstream>
#include <string>

static bool read_all(std::ifstream &in, std::string &out)
{
	char	c;

	out.clear();
	while (in.get(c))
		out.push_back(c);
	return (in.eof());
}

static std::string	replace_all(const std::string &src, const std::string &s1,
		const std::string &s2)
{
	std::string	result;
	std::size_t	i;

	result.clear();
	i = 0;
	while (i < src.size())
	{
		if (i + s1.size() <= src.size() && src.compare(i, s1.size(), s1) == 0)
		{
			result += s2;
			i += s1.size();
		}
		else
		{
			result.push_back(src[i]);
			i++;
		}
	}
	return (result);
}

int main (int argc, char **argv)
{
	std::string		filename;
	std::string		s1;
	std::string		s2;
	std::ifstream	in;
	std::ofstream	out;
	std::string		content;

	if (argc != 4)
	{
		std::cerr << "Usage: ./sed <filename> <s1> <s2>" << std::endl;
		return (1);
	}
	filename = argv[1];
	s1 = argv[2];
	s2 = argv[3];
	if (s1.empty())
	{
		std::cerr << "Error: s1 must not be empty." << std::endl;
		return (1);
	}

	in.open(filename.c_str());
	if (!in.is_open())
	{
		std::cerr << "Error: could not open input file." << std::endl;
		return (1);
	}
	if (!read_all(in, content))
	{
		std::cerr << "Error: could not read input file." << std::endl;
		return (1);
	}

	out.open((filename + ".replace").c_str());
	if (!out.is_open())
	{
		std::cerr << "Error: could not create output file." << std::endl;
		return (1);
	}
	out <<replace_all(content, s1, s2);
	return (0);
}
