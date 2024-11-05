/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:08:34 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/02 16:43:07 by tpinarli         ###   ########.fr       */
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
			p = &p[i];
			return (p);
		}
		i++;
	}
	return (p);
}

/*int	main()
{
	char	str[] = "Ali ata bak";
	int		c;
	char	*ptr;
	c = 't';
	ptr = ft_strchr(str, c);
	printf("%s", ptr);
	return (0);
}*/
