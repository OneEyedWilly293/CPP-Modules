NAME		= polymorphism

CXX			= c++

CXXFLAGS	= -Wall -Wextra -Werror -std=c++20

SRCS		= main.cpp \
			  Animal.cpp \
			  Dog.cpp \
			  Cat.cpp \
			  WrongAnimal.cpp \
			  WrongCat.cpp

OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking all object files to create the executable..."
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "Build successful! Run with ./$(NAME)"

clean:
	@echo "Removing object files..."
	rm -f $(OBJS)

fclean: clean
	@echo "Removing executable..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
