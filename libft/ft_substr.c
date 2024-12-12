/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:11:42 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/14 12:17:22 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		len1;
	int		index;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	len1 = (int)len;
	index = (int)start;
	if (start >= ft_strlen(s))
		len1 = 0;
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i != len1)
	{
		res[i] = s[index];
		index++;
		i++;
	}
	res[i] = '\0';
	return (res);
}
