/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:11:37 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 13:24:46 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	win_exit(t_game *game)
{
	ft_printf("YOU WON!!\n");
	mlx_close_window(game->mlx);
}

void	move_player(t_game *game, int new_x, int new_y, int prev_dir)
{
	int	x_pixel;
	int	y_pixel;

	x_pixel = new_y * PIXEL;
	y_pixel = new_x * PIXEL;
	game->map->p_start_x = new_x;
	game->map->p_start_y = new_y;
	if (game->map->p_direction_flag == 0)
		move_p_down(game, x_pixel, y_pixel, prev_dir);
	if (game->map->p_direction_flag == 1)
		move_p_up(game, x_pixel, y_pixel, prev_dir);
	if (game->map->p_direction_flag == 3)
		move_p_left(game, x_pixel, y_pixel, prev_dir);
	if (game->map->p_direction_flag == 2)
		move_p_right(game, x_pixel, y_pixel, prev_dir);
	if (game->map->map_array[new_x][new_y] == 'C')
	{
		game->map->collected++;
		game->map->map_array[new_x][new_y] = '0';
	}
	if (game->map->map_array[new_x][new_y] == 'E'
		&& game->map->collected == game->map->collectible_count)
		win_exit(game);
}

int	key_press_x_axis(t_game *game, mlx_key_data_t keydata, int new_x)
{
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
	{
		game->map->p_direction_flag = 1;
		new_x -= 1;
	}
	if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
	{
		game->map->p_direction_flag = 0;
		new_x += 1;
	}
	return (new_x);
}

int	key_press_y_axis(t_game *game, mlx_key_data_t keydata, int new_y)
{
	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
	{
		game->map->p_direction_flag = 3;
		new_y -= 1;
	}
	if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
	{
		game->map->p_direction_flag = 2;
		new_y += 1;
	}
	return (new_y);
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		new_x;
	int		new_y;
	int		prev_dir;

	game = (t_game *)param;
	if (keydata.action == MLX_RELEASE)
		return ;
	new_x = game->map->p_start_x;
	new_y = game->map->p_start_y;
	game->prev_x = new_x;
	game->prev_y = new_y;
	prev_dir = game->map->p_direction_flag;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	new_x = key_press_x_axis(game, keydata, new_x);
	new_y = key_press_y_axis(game, keydata, new_y);
	if (game->map->map_array[new_x][new_y] != '1')
		move_player(game, new_x, new_y, prev_dir);
	if (game->map->map_array[game->prev_x][game->prev_y] == 'E')
		mlx_image_to_window(game->mlx, game->exit_tile_p,
			game->prev_y * PIXEL, game->prev_x * PIXEL);
}
