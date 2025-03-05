# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 13:31:54 by tpinarli          #+#    #+#              #
#    Updated: 2025/02/23 17:28:57 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

CLIENT = client
SERVER = server

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}
OBJS_SERVER = ${SRCS_SERVER:.c=.o}

LIBFTDIR 	= ./libft
LIBFT 		= $(LIBFTDIR)/libft.a

PRINTFDIR	= ./printf
PRINTF		= $(PRINTFDIR)/libftprintf.a
INCLUDES 	= -I$(LIBFTDIR) -I$(PRINTFDIR)

all: $(SERVER) $(CLIENT)

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(PRINTF):
	$(MAKE) -C $(PRINTFDIR)

$(SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER) $(LIBFT) $(PRINTF)

$(CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT) $(LIBFT) $(PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(PRINTFDIR) clean

fclean: clean
	rm -f $(CLIENT) $(SERVER)
	$(MAKE) -C $(LIBFTDIR) fclean
	$(MAKE) -C $(PRINTFDIR) fclean

re: fclean all

.PHONY: all clean fclean re
