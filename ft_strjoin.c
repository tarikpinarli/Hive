/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:30:49 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/04 16:24:34 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*join;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(len * sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		join[i] = s2[j];
		i++;
		j++;
	}
	join[i] = '\0';
	return (join);
}

/*int main()
{
	char	s1[] = "Ali fsfsdsdfa";
	char	s2[] = "ta baksfsddfdsfs";
	char	*res;

	res = ft_strjoin(s1, s2);
	printf("%s", res);
	return (0);
}*/
