/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:01:29 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/01 19:39:10 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i] && i < n)
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

/*int main()
{
	char str1[] = "HelloWorld";
	char str2[] = "HelloWorlc";
	int val;
	int n;

	n = 10;
	val = ft_strncmp(str1, str2, n);
	printf("%d", val);
	
}*/
