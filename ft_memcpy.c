/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:22:34 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/01 21:00:23 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*point;
	char	*chp;
	int		i;
	point = (char*)dest;
	chp = (char*)src;
	if (!point && !chp)
		return (NULL);
	i = 0;
	while (i < n)
	{
		point[i] = chp[i];
		i++;
	}
	return (point);
}

/*int	main()
{
	char	src[11] = "HelloWorld";
	char	dest[11];
	ft_memcpy(dest, src, sizeof(src));
	printf("%s", src);
	printf("\n");
	printf("%s", dest);
	return (0);
}*/
