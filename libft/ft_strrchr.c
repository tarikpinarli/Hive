/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:29:25 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/14 12:11:25 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	p = (char *)s;
	i = ft_strlen(s);
	while (i != -1)
	{
		if (s[i] == c)
		{
			return (&p[i]);
		}
		i--;
	}
	if (c == '\0')
		return (&p[ft_strlen(s)]);
	return (NULL);
}
