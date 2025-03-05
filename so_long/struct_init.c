/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:24:44 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 14:31:55 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_struct_init(t_map **map)
{
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		print_error("t_map struct malloc failed.\n");
	(*map)->p_start_x = 0;
	(*map)->p_start_y = 0;
	(*map)->e_exit_x = 0;
	(*map)->e_exit_y = 0;
	(*map)->col_size = 0;
	(*map)->row_size = 0;
	(*map)->collected = 0;
	(*map)->collectible_count = 0;
	(*map)->start_count = 0;
	(*map)->exit_count = 0;
	(*map)->p_direction_flag = 0;
	(*map)->visited = NULL;
	(*map)->map_array = NULL;
}

void	init_rest(t_game **game)
{
	(*game)->prev_x = 0;
	(*game)->prev_y = 0;
	(*game)->move_count = 0;
	(*game)->down_left_p = NULL;
	(*game)->down_right_p = NULL;
	(*game)->up_right_p = NULL;
	(*game)->up_left_p = NULL;
	(*game)->player_left_p = NULL;
	(*game)->player_right_p = NULL;
	(*game)->prev_v_p = NULL;
	(*game)->prev_p = NULL;
	(*game)->collectible_p = NULL;
	(*game)->exit_tile_p = NULL;
	(*game)->grass_p = NULL;
	(*game)->player_down_p = NULL;
	(*game)->wall_p = NULL;
	(*game)->mlx = NULL;
}

void	game_struct_init(t_game **game, t_map *map)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!*game)
	{
		free_map_struct(map);
		print_error("t_game struct malloc  failed.\n");
	}
	(*game)->map = map;
	(*game)->name = "so_long";
	(*game)->width = PIXEL * map->col_size;
	(*game)->height = PIXEL * map->row_size;
	(*game)->player_down = mlx_load_png("png/player_down.png");
	(*game)->grass = mlx_load_png("png/grass.png");
	(*game)->collectible = mlx_load_png("png/collectible.png");
	(*game)->exit_tile = mlx_load_png("png/exit.png");
	(*game)->wall = mlx_load_png("png/wall.png");
	(*game)->prev = mlx_load_png("png/prev.png");
	(*game)->prev_v = mlx_load_png("png/prev_v.png");
	(*game)->player_right = mlx_load_png("png/player_right.png");
	(*game)->player_left = mlx_load_png("png/player_left.png");
	(*game)->player_up = mlx_load_png("png/player_up.png");
	(*game)->up_left = mlx_load_png("png/up_left.png");
	(*game)->up_right = mlx_load_png("png/up_right.png");
	(*game)->down_right = mlx_load_png("png/down_right.png");
	(*game)->down_left = mlx_load_png("png/down_left.png");
	init_rest(game);
}
