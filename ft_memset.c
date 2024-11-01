/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:21:42 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/01 19:17:56 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;
	int		i;
	i = 0;
	p = (char*)s;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (s);
}

/*int	main()
{
	char	s[] = "tarik pinarli"; 
	int	c = '.';
	size_t	n = 3;
	ft_memset(s + 2, c, n);

	printf("%s", s);
	return (0);
}*/
