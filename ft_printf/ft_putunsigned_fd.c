/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:32:49 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/28 15:12:50 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned_fd(unsigned int nb, int fd)
{
	unsigned int	res;

	res = 0;
	if (nb > 9)
	{
		res += ft_putunsigned_fd(nb / 10, fd);
		res += ft_putunsigned_fd(nb % 10, fd);
	}
	else
		res += ft_putchar_fd(nb + 48, fd);
	return (res);
}
