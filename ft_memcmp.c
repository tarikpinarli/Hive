/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:39:45 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/02 17:53:19 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*sp1;
	char	*sp2;
	int		i;
	int		nb;

	sp1 = (char *)s1;
	sp2 = (char *)s2;
	i = 0;
	nb = (int)n;
	while (i != nb)
	{
		if (sp1[i] != sp2[i])
			return (sp1[i] - sp2[i]);
		i++;
	}
	return (0);
}

/*int main()
{
	char	str1[] = "Ali ata bak";
	char	str2[] = "Ali bta bak";
	size_t	n;
	int		res;

	n = 0;
	res = ft_memcmp(str1, str2, n);
	printf("%d", res);
	return (0);
}*/
