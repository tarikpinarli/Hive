/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:36:22 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/10 15:26:06 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**size(char const *s, char c, char **array, int count);
int		split_count(char const *s, char c);
char	**sub_array_size(char const *s, char c, char **array, int count);
char	**ch_alloc(char const *s, char c, char **array);
void	free_array(char **array, int count);

void	free_array(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**array;

	count = split_count(s, c);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = sub_array_size(s, c, array, count);
	array = ch_alloc(s, c, array);
	return (array);
}

char	**sub_array_size(char const *s, char c, char **array, int count)
{
	int	i;
	int	len;

	i = 0;
	while (i < count)
	{
		while (*s == c && *s != '\0')
			s++;
		len = 0;
		while (*s != c && *s != '\0')
		{
			len++;
			s++;
		}
		array[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!array[i])
		{
			free_array(array, i);
			return (NULL);
		}
		i++;
	}
	array[count] = NULL;
	return (array);
}

char	**ch_alloc(char const *s, char c, char **array)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	k = 0;
	j = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (s[k] == c && s[k] != '\0')
			k++;
		while (s[k] != '\0' && s[k] != c)
		{
			array[i][j] = s[k];
			j++;
			k++;
		}
		array[i][j] = '\0';
		i++;
	}
	return (array);
}

int	split_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (s[0] == '\0')
		return (count);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

/*int	main(void)
{
	char	*s = "_as_________s_Ali_ata___a";
	char	c = '_';
	char	**res;
	int		i;

	res = ft_split(s, c);
	i = 0;
	while (res[i] != NULL)
	{
		printf("%s\n", res[i]);
		i++;
	}
	printf("word count: %d\n", split_count(s, c));
	return (0);
}*/
