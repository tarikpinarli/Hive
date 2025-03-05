/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:11:42 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 14:29:05 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_p_down(t_game *game, int x_pixel, int y_pixel, int prev_dir)
{
	int	prev_step;
	int	new_x;
	int	new_y;

	new_x = game->map->p_start_x;
	new_y = game->map->p_start_y;
	prev_step = y_pixel - PIXEL;
	game->move_count++;
	ft_printf("Move count: %d\n", game->move_count);
	mlx_image_to_window(game->mlx, game->player_down_p, x_pixel, y_pixel);
	if (prev_dir == 3)
		mlx_image_to_window(game->mlx, game->up_right_p, x_pixel, prev_step);
	else if (prev_dir == 2)
		mlx_image_to_window(game->mlx, game->up_left_p, x_pixel, prev_step);
	else
		mlx_image_to_window(game->mlx, game->prev_v_p, x_pixel, prev_step);
	if (game->map->map_array[new_x][new_y] == 'C')
	{
		game->map->collected++;
		game->map->map_array[new_x][new_y] = '0';
	}
}

void	move_p_up(t_game *game, int x_pixel, int y_pixel, int prev_dir)
{
	int	prev_step;
	int	new_x;
	int	new_y;

	new_x = game->map->p_start_x;
	new_y = game->map->p_start_y;
	prev_step = y_pixel + PIXEL;
	game->move_count++;
	ft_printf("Move count: %d\n", game->move_count);
	mlx_image_to_window(game->mlx, game->player_up_p, x_pixel, y_pixel);
	if (prev_dir == 3)
		mlx_image_to_window(game->mlx, game->down_right_p, x_pixel, prev_step);
	else if (prev_dir == 2)
		mlx_image_to_window(game->mlx, game->down_left_p, x_pixel, prev_step);
	else
		mlx_image_to_window(game->mlx, game->prev_v_p, x_pixel, prev_step);
	if (game->map->map_array[new_x][new_y] == 'C')
	{
		game->map->collected++;
		game->map->map_array[new_x][new_y] = '0';
	}
}

void	move_p_left(t_game *game, int x_pixel, int y_pixel, int prev_dir)
{
	int	prev_step;
	int	new_x;
	int	new_y;

	new_x = game->map->p_start_x;
	new_y = game->map->p_start_y;
	prev_step = x_pixel + PIXEL;
	game->move_count++;
	ft_printf("Move count: %d\n", game->move_count);
	mlx_image_to_window(game->mlx, game->player_left_p, x_pixel, y_pixel);
	if (prev_dir == 1)
		mlx_image_to_window(game->mlx, game->up_left_p, prev_step, y_pixel);
	else if (prev_dir == 0)
		mlx_image_to_window(game->mlx, game->down_left_p, prev_step, y_pixel);
	else
		mlx_image_to_window(game->mlx, game->prev_p, prev_step, y_pixel);
	if (game->map->map_array[new_x][new_y] == 'C')
	{
		game->map->collected++;
		game->map->map_array[new_x][new_y] = '0';
	}
}

void	move_p_right(t_game *game, int x_pixel, int y_pixel, int prev_dir)
{
	int	prev_step;
	int	new_x;
	int	new_y;

	new_x = game->map->p_start_x;
	new_y = game->map->p_start_y;
	prev_step = x_pixel - PIXEL;
	game->move_count++;
	ft_printf("Move count: %d\n", game->move_count);
	mlx_image_to_window(game->mlx, game->player_right_p, x_pixel, y_pixel);
	if (prev_dir == 1)
		mlx_image_to_window(game->mlx, game->up_right_p, prev_step, y_pixel);
	else if (prev_dir == 0)
		mlx_image_to_window(game->mlx, game->down_right_p, prev_step, y_pixel);
	else
		mlx_image_to_window(game->mlx, game->prev_p, prev_step, y_pixel);
	if (game->map->map_array[new_x][new_y] == 'C')
	{
		game->map->collected++;
		game->map->map_array[new_x][new_y] = '0';
	}
}
