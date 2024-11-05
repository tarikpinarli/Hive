/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:03:34 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/02 16:08:09 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c <= 90 && c >= 65)
	{
		c = c + 32;
	}
	return (c);
}

/*int main()
{
	int val;
	int  res;
	val = '0';
	res = ft_tolower(val);
	printf("%c", res);
	return (0);
}*/
