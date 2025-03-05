/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:31:03 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 15:37:35 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	texture_to_image(mlx_t *mlx, t_game *game, t_map *map)
{
	game->grass_p = mlx_texture_to_image(mlx, game->grass);
	game->collectible_p = mlx_texture_to_image(mlx, game->collectible);
	game->exit_tile_p = mlx_texture_to_image(mlx, game->exit_tile);
	game->player_down_p = mlx_texture_to_image(mlx, game->player_down);
	game->wall_p = mlx_texture_to_image(mlx, game->wall);
	game->prev_p = mlx_texture_to_image(mlx, game->prev);
	game->prev_v_p = mlx_texture_to_image(mlx, game->prev_v);
	game->player_right_p = mlx_texture_to_image(mlx, game->player_right);
	game->player_left_p = mlx_texture_to_image(mlx, game->player_left);
	game->player_up_p = mlx_texture_to_image(mlx, game->player_up);
	game->up_left_p = mlx_texture_to_image(mlx, game->up_left);
	game->up_right_p = mlx_texture_to_image(mlx, game->up_right);
	game->down_right_p = mlx_texture_to_image(mlx, game->down_right);
	game->down_left_p = mlx_texture_to_image(mlx, game->down_left);
	if (!game->player_down_p || !game->player_up_p || !game->player_right_p
		|| !game->up_right_p || !game->up_left_p || !game->down_right_p
		|| !game->down_left_p || !game->player_left_p || !game->collectible_p
		|| !game->exit_tile_p || !game->wall_p || !game->grass_p
		|| !game->prev_p || !game->prev_v_p)
	{
		free_map_struct(map);
		free_game_struct(game);
		print_error("Error loading textures.\n");
	}
}
