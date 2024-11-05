/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:53:56 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/04 15:36:06 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	match(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(set))
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		y;
	int		x;
	int		max;
	char	*res;

	i = 0;
	y = 0;
	x = 0;
	res = (char *)malloc(ft_strlen(s1) * sizeof(char));
	if (!res)
		return (NULL);
	max = ft_strlen(s1);
	while (match(s1[i], set) == 1)
		i++;
	while (match(s1[max - 1], set) == 1)
		max--;
	while (i < max)
		res[x++] = s1[i++];
	res[x] = '\0';
	return (res);
}

/*int	main(void)
{
	char	s1[] = "aliatabak dsvvvdv biraliatabak kiraliatabakj";
	char	set[] = "aaliatabak";
	char	*res;

	res = ft_strtrim(s1, set);
	printf("%s", res);
	return (0);
}*/
