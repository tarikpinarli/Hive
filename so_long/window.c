/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:10:13 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 15:37:03 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_map(mlx_t *mlx, t_map *map, t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (map->map_array[i])
	{
		j = 0;
		while (map->map_array[i][j])
		{
			x = j * PIXEL;
			y = i * PIXEL;
			if (map->map_array[i][j] == '1')
				mlx_image_to_window(mlx, game->wall_p, x, y);
			if (map->map_array[i][j] == 'P')
				mlx_image_to_window(mlx, game->player_down_p, x, y);
			if (map->map_array[i][j] == 'C')
				mlx_image_to_window(mlx, game->collectible_p, x, y);
			if (map->map_array[i][j] == 'E')
				mlx_image_to_window(mlx, game->exit_tile_p, x, y);
			j++;
		}
		i++;
	}
}

void	render_background(mlx_t *mlx, t_map *map_pointer, t_game *game)
{
	char	**map;
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	map = map_pointer->map_array;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			x = j * PIXEL;
			y = i * PIXEL;
			mlx_image_to_window(mlx, game->grass_p, x, y);
			j++;
		}
		i++;
	}
}

void	start_window(t_map *map, t_game *game)
{
	mlx_t	*mlx;

	mlx = mlx_init(game->width, game->height, game->name, true);
	if (!mlx)
	{
		free_map_struct(map);
		free_game_struct(game);
		print_error("mlx_init failed.\n");
	}
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx = mlx;
	texture_to_image(mlx, game, map);
	render_background(mlx, map, game);
	render_map(mlx, map, game);
	mlx_key_hook(mlx, handle_keypress, game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
