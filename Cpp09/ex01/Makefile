NAME     = RPN
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20

# Colors
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
RESET   = \033[0m

SRCS     = main.cpp RPN.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

%.o: %.cpp
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	rm -f $(OBJS)

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
