/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:47:46 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 12:54:48 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_collectibles(t_map *map_point)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map_point->map_array[i])
	{
		j = 0;
		while (map_point->map_array[i][j])
		{
			if (map_point->map_array[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	map_point->collectible_count = count;
}

void	find_start_point(t_map *map_point)
{
	int	i;
	int	j;

	i = 0;
	while (map_point->map_array[i])
	{
		j = 0;
		while (map_point->map_array[i][j])
		{
			if (map_point->map_array[i][j] == 'P')
			{
				map_point->p_start_x = i;
				map_point->p_start_y = j;
			}
			j++;
		}
		i++;
	}
}

void	find_exit_point(t_map *map_point)
{
	int	i;
	int	j;

	i = 0;
	while (map_point->map_array[i])
	{
		j = 0;
		while (map_point->map_array[i][j])
		{
			if (map_point->map_array[i][j] == 'E')
			{
				map_point->e_exit_x = i;
				map_point->e_exit_y = j;
			}
			j++;
		}
		i++;
	}
}

void	visited_array_alloc(t_map *map_point)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(map_point->row_size * sizeof(int *));
	if (!visited)
	{
		free_map_struct(map_point);
		print_error("Error mallocing visited ineger array.\n");
	}
	i = 0;
	while (i < map_point->row_size)
	{
		visited[i] = (int *)malloc(map_point->col_size * sizeof(int));
		if (!visited[i])
		{
			free_map_struct(map_point);
			print_error("Error mallocing visited ineger array.\n");
		}
		j = 0;
		while (j < map_point->col_size)
			visited[i][j++] = 0;
		i++;
	}
	map_point->visited = visited;
}
