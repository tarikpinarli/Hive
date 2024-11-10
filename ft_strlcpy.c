/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 21:00:41 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/08 12:00:08 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		res;

	res = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (res);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > i)
		dst[i] = '\0';
	return (res);
}

/*int main()
{
	char	str[] = "Ali ata bak";
	char	dest[11];
	size_t	size = 11;

	ft_strlcpy(dest, str, size);
	printf("%s", dest);
	return (0);
}*/
