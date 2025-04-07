NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

# Sanitizer flags
FSANITIZER_ADDRESS_FLAG = -fsanitize=address -O2
FSANITIZER_THREAD_FLAG = -fsanitize=thread -O2
VALGRIND_FLAG = -g -O2
HELGRIND_FLAG = -g -O2

SRC = \
		main.c free.c arg_handle_utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

# Aliases
asan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_ADDRESS_FLAG)" all
tsan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_THREAD_FLAG)" all
valgrind:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(VALGRIND_FLAG)" all
	valgrind ./$(NAME) $(ARGS)
helgrind:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(HELGRIND_FLAG)" all
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

.PHONY : all clean fclean re
