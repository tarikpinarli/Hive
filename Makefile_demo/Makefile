# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/30 15:20:21 by tpinarli          #+#    #+#              #
#    Updated: 2024/10/30 16:09:08 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_atoi.c ft_strncmp.c
OBJ = $(SRC:.c=.o)
$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)
%.c:%.o
	$(CC) $(CFLAGS) -c $< -o $@
all:$(name)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all


