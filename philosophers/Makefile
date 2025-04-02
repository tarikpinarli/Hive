# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 13:09:26 by tpinarli          #+#    #+#              #
#    Updated: 2025/04/01 14:44:45 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= philo
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -g


OBJ_DIR		= obj/

SRCS =	main.c arg_handle_utils.c error_exit.c free.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
