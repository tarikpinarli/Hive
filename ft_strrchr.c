/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:29:25 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/02 16:56:17 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*p;

	p = (char *)s;
	i = ft_strlen(s);
	while (i != 0)
	{
		if (s[i] == c)
		{
			p = &p[i];
			return (p);
		}
		i--;
	}
	return (p);
}

/*int  main()
{
	char	str[] = "-li ata bak";
	int		ch;
	char	*pt;
	ch = '-';
	pt = ft_strrchr(str, ch);
	printf("%s", pt);
	return (0);
}*/
