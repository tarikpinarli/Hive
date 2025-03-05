/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:08:59 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 14:08:12 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_rectangular_fail(t_map *map_point, char *line, int fd)
{
	free_map_struct(map_point);
	free_buffer_close(line, fd);
	print_error("Map is not rectangular or empty line found.\n");
}

void	free_map_struct(t_map *map_point)
{
	if (!map_point)
		return ;
	if (map_point->map_array)
		free_matrix(map_point->map_array);
	if (map_point->visited)
		free_int_matrix(map_point->visited, map_point->row_size);
	free(map_point);
}

void	free_int_matrix(int **matrix, int rows)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < rows)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	free_buffer_close(char *line, int fd)
{
	char	*ptr;

	free(line);
	ptr = "";
	while (ptr)
	{
		ptr = get_next_line(fd);
		if (!ptr)
			break ;
		free(ptr);
	}
	close(fd);
}
