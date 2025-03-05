/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:18:23 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 14:00:53 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_fd(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		print_error("Opening map failed.\n");
	return (fd);
}

int	row_size(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

int	col_size(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (i);
}

void	wall_check(t_map *map_point)
{
	char	**map;
	int		i;

	map = map_point->map_array;
	i = 0;
	while (i < map_point->col_size)
	{
		if (map[0][i] != '1' || map[map_point->row_size - 1][i] != '1')
		{
			free_map_struct(map_point);
			print_error("Map is not surrounded by walls.\n");
		}
		i++;
	}
	i = 0;
	while (i < map_point->row_size)
	{
		if (map[i][0] != '1' || map[i][map_point->col_size - 1] != '1')
		{
			free_map_struct(map_point);
			print_error("Map is not surrounded by walls.\n");
		}
		i++;
	}
}
