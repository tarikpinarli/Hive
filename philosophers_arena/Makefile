# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/25 17:52:42 by tpinarli          #+#    #+#              #
#    Updated: 2025/05/26 16:25:03 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

# Sanitizer flags
ASAN_FLAGS = -fsanitize=address -O2
TSAN_FLAGS = -fsanitize=thread -O2
VALGRIND_FLAGS = -g -O2
HELGRIND_FLAGS = -g -O2

SRC = \
	main.c \
	arena.c \
	utils/input_check.c \
	utils/ft_atoi.c \
	utils/time.c \
	init/init_table.c \
	init/init_forks.c \
	init/init_philos.c \
	init/setup_table.c \
	simulation/philo_routine.c \
	simulation/control.c \
	simulation/monitor_death.c \
	simulation/setup_philos.c \
	simulation/philo_think.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Default target
all: $(NAME)

# Link object files
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)


# Create obj directory if not exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -rf $(OBJ_DIR)

# Clean all
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

# Flag-based builds
asan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(ASAN_FLAGS)" all

tsan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(TSAN_FLAGS)" all

valgrind:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(VALGRIND_FLAGS)" all
	valgrind ./$(NAME) $(ARGS)

helgrind:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(HELGRIND_FLAGS)" all
	valgrind --tool=helgrind ./$(NAME) $(ARGS)

.PHONY: all clean fclean re asan tsan valgrind helgrind

