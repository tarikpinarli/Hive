/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:19:39 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/01 20:58:00 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	//char	*temp;
	char	*srcp;
	char	*destp;
	size_t	i;
	if (!srcp && !destp)
		return (NULL);
	srcp = (char*)src;
	destp = (char*)dest;
	i = 0;
	if (destp > srcp)
		while (n--)
			destp[n] = srcp[n];
	while (i < n)
	{
		destp[i] = srcp[i];
		i++;
	}
	destp[i] = '\0';
	return (destp);
}

/*int main()
{
	const char	src[] = "HelloWorld";
	char	dest[11];
	size_t	n;
	n = 10;
	ft_memmove(dest, src+5, n);
	//memmove(dest, src, n);
	printf("%s\n", src);
	printf("%s", dest);
	return (0);
}*/
