# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/05 13:09:26 by tpinarli          #+#    #+#              #
#    Updated: 2025/03/07 16:32:17 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 		= philo
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror


PRINTFDIR	= ./printf
PRINTF		= $(PRINTFDIR)/libftprintf.a


INCLUDES 	= -I $(PRINTFDIR)
OBJ_DIR		= obj/

SRCS =	main.c arg_handle_utils.c error_exit.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(PRINTF):
	@$(MAKE) -C $(PRINTFDIR)

$(NAME): $(OBJS) $(PRINTF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTF)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(PRINTFDIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(PRINTFDIR) fclean

re: fclean all

.PHONY: all clean fclean re
