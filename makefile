NAME = expert_system

SRC = Main.cpp\
      ReadInfo.cpp\
	  ExpSysClass.cpp\
	  MemberClass.cpp\
	  Solver.cpp\
	  WriteInfo.cpp\
	  CheckExpression.cpp\
	  BonusPart.cpp


OBJ		= $(addprefix $(OBJDIR),$(SRC:.cpp=.o))

SRCDIR	= ./src/
INCDIR	= ./inc/
OBJDIR	= ./obj/

CC = clang++

FLAGS = -Wall -Wextra -Werror

all: obj $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.cpp
	$(CC) $(FLAGS) -I $(INCDIR) -o $@ -c $<


$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJDIR)

fclean: clean
		rm -f $(NAME)

re: fclean all