/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game_operations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:52:55 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 13:01:09 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_rest_textures(t_game *game)
{
	if (game->grass)
		mlx_delete_texture(game->grass);
	if (game->wall)
		mlx_delete_texture(game->wall);
	if (game->exit_tile)
		mlx_delete_texture(game->exit_tile);
	if (game->collectible)
		mlx_delete_texture(game->collectible);
}

void	free_path_textures(t_game *game)
{
	if (game->down_left)
		mlx_delete_texture(game->down_left);
	if (game->down_right)
		mlx_delete_texture(game->down_right);
	if (game->up_left)
		mlx_delete_texture(game->up_left);
	if (game->up_right)
		mlx_delete_texture(game->up_right);
	if (game->prev_v)
		mlx_delete_texture(game->prev_v);
	if (game->prev)
		mlx_delete_texture(game->prev);
}

void	free_player_textures(t_game *game)
{
	if (game->player_down)
		mlx_delete_texture(game->player_down);
	if (game->player_up)
		mlx_delete_texture(game->player_up);
	if (game->player_left)
		mlx_delete_texture(game->player_left);
	if (game->player_right)
		mlx_delete_texture(game->player_right);
}

void	free_game_struct(t_game *game)
{
	if (!game)
		return ;
	free_player_textures(game);
	free_path_textures(game);
	free_rest_textures(game);
	free(game);
}
