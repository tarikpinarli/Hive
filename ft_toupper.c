/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:50:09 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/02 16:02:46 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c <= 122 && c >= 97)
	{
		c = c - 32;
	}
	return (c);
}

/*int	main()
{
	int	ch = '9';
	char	res;
	res = ft_toupper(ch);
	printf("%c", res);
	return (0);
}*/
