# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/18 16:05:50 by tpinarli          #+#    #+#              #
#    Updated: 2025/02/18 16:05:53 by tpinarli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= so_long
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror

LIBFTDIR 	= ./libft
LIBFT 		= $(LIBFTDIR)/libft.a

PRINTFDIR	= ./printf
PRINTF		= $(PRINTFDIR)/libftprintf.a

MLX42DIR    = ./MLX42
MLX42BUILD  = $(MLX42DIR)/build
MLX42LIB    = -L $(MLX42DIR)/build -lmlx42 -L /usr/lib -lglfw -ldl -pthread -lm
MLX42INC    = -I $(MLX42DIR)/include

INCLUDES 	= -I $(LIBFTDIR) -I $(PRINTFDIR) $(MLX42INC)
OBJ_DIR		= obj/

SRCS =	arg_validation.c error_utils.c main.c \
		map_validation.c free_map_operations.c struct_init.c free_game_operations.c \
		flood_fill.c flood_fill_utils.c map_validation_utils.c window.c window_utils.c \
		handle_keypress.c gnl/get_next_line.c gnl/get_next_line_utils.c move_player.c

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(MLX42BUILD) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(PRINTF):
	@$(MAKE) -C $(PRINTFDIR)

$(MLX42BUILD):
	@if [ ! -d "$(MLX42DIR)" ]; then git clone https://github.com/codam-coding-college/MLX42.git $(MLX42DIR); fi
	cmake -B $(MLX42BUILD) -S $(MLX42DIR) -D CMAKE_BUILD_TYPE=Release
	$(MAKE) -C $(MLX42BUILD)

$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(PRINTF) $(MLX42LIB)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFTDIR) clean
	@$(MAKE) -C $(PRINTFDIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean
	@$(MAKE) -C $(PRINTFDIR) fclean
	rm -f $(MLX42)

re: fclean all

.PHONY: all clean fclean re
