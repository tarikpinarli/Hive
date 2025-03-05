/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:53:13 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 12:58:14 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(int x, int y, t_map *map_point)
{
	if (x < 0 || x >= map_point->row_size || y < 0 || y >= map_point->col_size)
		return ;
	if (map_point->map_array[x][y] == '1' || map_point->visited[x][y])
		return ;
	map_point->visited[x][y] = 1;
	if (map_point->map_array[x][y] == 'C')
		map_point->collected++;
	flood_fill(x + 1, y, map_point);
	flood_fill(x - 1, y, map_point);
	flood_fill(x, y + 1, map_point);
	flood_fill(x, y - 1, map_point);
}

void	flood_fill_check(t_map *map_point)
{
	visited_array_alloc(map_point);
	find_start_point(map_point);
	find_exit_point(map_point);
	count_collectibles(map_point);
	flood_fill(map_point->p_start_x, map_point->p_start_y, map_point);
	if (map_point->visited[map_point->e_exit_x][map_point->e_exit_y] == 0
		|| map_point->collected != map_point->collectible_count)
	{
		free_map_struct(map_point);
		print_error("Exit is unreachable or collectibles were missed.\n");
	}
	map_point->collected = 0;
}
