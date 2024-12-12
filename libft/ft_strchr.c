/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:08:34 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/14 12:10:46 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*p;

	i = 0;
	p = (char *)s;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			return (&p[i]);
		}
		i++;
	}
	if (c == '\0')
		return (&p[i]);
	return (NULL);
}
