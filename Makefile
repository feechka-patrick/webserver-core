# DIRECTIRIES -------------

ODIR = ./srcs

SDIR = ./srcs

INCDIR = ./incs

# MAIN PROGRAM ------------

SRC = $(SDIR)/main.cpp $(SDIR)/Client.cpp $(SDIR)/Server.cpp

# OBJ = $(SRC:.cpp=.o)
OBJ = $(SRC:$(SDIR)/%.cpp=$(ODIR)/%.o)

DEPS = $(OBJ:.o=.d)

NAME = ./webserver


# TEST --------------------

SRC_TEST = ./src/tests.cpp ./src/utils.cpp

OBJ_TEST = $(SRC_TEST:$(SDIR)/%.cpp=$(ODIR)/%.o)

DEPS_TEST = $(OBJ_TEST:.o=.d)

NAME_TEST = ./test


# FLAGS AND OTHER ---------
CXX = clang++

DEPFLAGS = -MMD -MF $(@:.o=.d)

CFLAG = -Wall -Wextra -Werror -std=c++98 -g

RM = rm -rf

# RULES -------------------

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CFLAG) -I./$(INCDIR) $(OBJ) -o $(NAME)
-include $(DEPS)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CXX) $(CFLAG) -I./$(INCDIR) -c $< $(DEPFLAGS)  -o $@

%.o: %.cpp
	$(CXX) $(CFLAG) -I./$(INCDIR) -c $< $(DEPFLAGS) -o $@

clean:
	@$(RM) $(OBJ)
	@$(RM) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

test: $(OBJ_TEST)
	$(CXX) $(CFLAG) -I./$(INCDIR) $(OBJ_TEST) -o $(NAME_TEST)
-include $(DEPS_TEST)


re: fclean all

.PHONY:	all clean fclean re