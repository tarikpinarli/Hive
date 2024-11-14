/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:59:59 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/14 12:10:25 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int		i;
	int		nb;
	char	*p;

	p = (char *)s;
	nb = (int)n;
	i = 0;
	while (i != nb)
	{
		if (p[i] == c)
		{
			p = &p[i];
			return (p);
		}
		i++;
	}
	p = NULL;
	return (p);
}
