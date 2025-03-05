/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:51:26 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 14:19:45 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	copy_map(int fd, t_map *map_point)
{
	char	**map_array;
	int		i;

	i = 0;
	map_array = (char **)malloc((map_point->row_size + 1) * sizeof(char *));
	if (!map_array)
		print_error("map_copy mallocing failed.\n");
	while (i < map_point->row_size)
	{
		map_array[i] = get_next_line(fd);
		if (!map_array[i])
		{
			free_map_struct(map_point);
			close(fd);
			print_error("map_copy mallocing failed.\n");
		}
		i++;
	}
	map_array[i] = NULL;
	map_point->map_array = map_array;
	if (!map_point->map_array)
		print_error("Map copy error.\n");
	close(fd);
}

void	component_counter(t_map *map_point)
{
	int	i;
	int	j;

	i = 0;
	while (map_point->map_array[i] != NULL)
	{
		j = 0;
		while (map_point->map_array[i][j] != '\0')
		{
			if (map_point->map_array[i][j] == 'C')
				map_point->collectible_count++;
			else if (map_point->map_array[i][j] == 'E')
				map_point->exit_count++;
			else if (map_point->map_array[i][j] == 'P')
				map_point->start_count++;
			j++;
		}
		i++;
	}
	if (map_point->collectible_count < 1 || map_point->exit_count != 1
		|| map_point->start_count != 1)
	{
		free_map_struct(map_point);
		print_error("Component missing or extra.\n");
	}
}

void	component_check(t_map *map_point)
{
	int		i;
	int		j;
	char	ch;

	i = 0;
	component_counter(map_point);
	while (map_point->map_array[i])
	{
		j = 0;
		while (map_point->map_array[i][j])
		{
			ch = map_point->map_array[i][j];
			if (ch != '0' && ch != '1' && ch != 'C' && ch != 'E' && ch != 'P')
			{
				free_map_struct(map_point);
				print_error("Invalid character found in map.\n");
			}
			j++;
		}
		i++;
	}
}

void	rectangular_check(int fd, t_map *map_point)
{
	char	*line;
	int		line_num;

	line_num = 0;
	line = get_next_line(fd);
	if (!line)
	{
		free_map_struct(map_point);
		print_error("Map file is empty.\n");
	}
	map_point->col_size = col_size(line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_num++;
		if (map_point->col_size != col_size(line) || line[0] == '\0')
			free_rectangular_fail(map_point, line, fd);
		free(line);
	}
	map_point->row_size = line_num + 1;
	close(fd);
}

void	map_validation(char *file_name, t_map *map_point)
{
	rectangular_check(get_fd(file_name), map_point);
	copy_map(get_fd(file_name), map_point);
	component_check(map_point);
	wall_check(map_point);
	flood_fill_check(map_point);
}
