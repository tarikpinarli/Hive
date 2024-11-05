/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:11:42 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/04 14:29:32 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		len1;
	int		index;
	char	*str;
	char	*res;

	i = 0;
	len1 = (int)len;
	str = (char *)s;
	index = (int)start;
	res = (char *)malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	while (i != len1)
	{
		res[i] = s[index];
		index++;
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*int main()
{
	char	s[] = "Ali ata bak";
	size_t	len;
	int		start;
	char	*res;

	len = 10;
	start = 5;
	res = ft_substr(s, start, len);
	printf("%s", res);
	return (0);
}*/
