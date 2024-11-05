/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:36:22 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/04 18:01:33 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**size(char const *s, char c, char **array, int count);
int		split_count(char const *s, char c);
char	**sub_array_size(char const *s, char c, char **array, int count);
char	**ch_alloc(char const *s, char c, char **array);

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
	int	k;
	int	len;

	i = 0;
	k = 0;
	while (i < count)
	{
		len = 0;
		while (s[k] != '\0' && s[k] != c)
		{
			k++;
			len++;
		}
		array[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!array[i])
		{
			free(array);
			return (NULL);
		}
		k++;
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
		while (s[k] != '\0' && s[k] != c)
		{
			array[i][j] = s[k];
			j++;
			k++;
		}
		array[i][j] = '\0';
		k++;
		i++;
	}
	return (array);
}

int	split_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

/*int	main(void)
{
	char	*s = "__Ali_ata_bak._";
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
	return (0);
}*/
