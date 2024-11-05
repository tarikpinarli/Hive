/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:59:59 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/02 17:38:56 by tpinarli         ###   ########.fr       */
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

/*int main()
{
	const char	s[] = "Ali ata bak";
	int	c;
	size_t	n;
	char	*p;
	c = 'l';
	n = 5;
	p = ft_memchr(s, c, n);
	printf("%s", p);
	return (0);
}*/
