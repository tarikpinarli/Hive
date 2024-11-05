/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:58:26 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/02 18:28:00 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	allmatch(char *big, char *little, int len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	int		len1;
	char	*large;
	char	*small;

	large = (char *)big;
	small = (char *)little;
	len1 = (int)len;
	i = 0;
	if (small[0] == '\0')
		return (large);
	while (big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			if (allmatch(&large[i], small, len1) == 1)
			{
				return (&large[i]);
			}
		}
		i++;
	}
	return (NULL);
}

int	allmatch(char *big, char *little, int len)
{
	int	i;
	int	len1;

	i = 0;
	len1 = len;
	while (len1 != 0)
	{
		if (big[i] != little[i])
			return (0);
		i++;
		len1--;
	}
	return (1);
}

/*int	main()
{
	const char	largestring[] = "Foo Bar Baz";
	const char	littlestring[] = "";
	size_t	len;
	char	*ptr;

	len = 1;
	ptr = ft_strnstr(largestring, littlestring, len);
	printf("%s", ptr);
	return (0);
}*/
