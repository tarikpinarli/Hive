/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:58:52 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/17 12:40:59 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*buffer_update(char *buffer)
{
	int		i;
	int		j;
	char	*newbuffer;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	newbuffer = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	i++;
	if (!newbuffer)
		return (NULL);
	while (buffer[i])
		newbuffer[j++] = buffer[i++];
	free(buffer);
	return (newbuffer);
}

char	*next_line(char *buffer)
{
	char	*new_line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	new_line = ft_calloc(i + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		new_line[i] = buffer[i];
		i++;
	}
	new_line[i] = 0;
	return (new_line);
}

char	*free_and_join(char *buffer, char *result)
{
	char	*temp;

	temp = ft_strjoin(buffer, result);
	free(buffer);
	return (temp);
}

char	*read_buffer(char *buffer, int fd)
{
	char	*result;
	int		read_byte;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	result = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!result)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, result, BUFFER_SIZE);
		if (read_byte == -1)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		result[read_byte] = 0;
		buffer = free_and_join(buffer, result);
		if (ft_strchr(result, '\n'))
			break ;
	}
	free(result);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*new_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = read_buffer(buffer, fd);
	if (!buffer)
	{
		free(buffer);
		return (NULL);
	}
	new_line = next_line(buffer);
	buffer = buffer_update(buffer);
	return (new_line);
}
