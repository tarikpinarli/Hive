# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/25 11:12:42 by tpinarli          #+#    #+#              #
#    Updated: 2024/11/25 11:45:09 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS = ft_printf.c	 ft_puthex_fd.c       ft_putnbr_fd.c  ft_putunsigned_fd.c\
	   ft_putchar_fd.c  ft_putlowerhex_fd.c  ft_putstr_fd.c  ft_putupperhex.c	   ft_strlen.c\

OBJS = ${SRCS:.c=.o}

CC = cc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

all: ${NAME}

clean:
	${RM} ${OBJS}


fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
