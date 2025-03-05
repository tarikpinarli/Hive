/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:32:49 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/12 12:52:03 by tpinarli         ###   ########.fr       */
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
		res += ft_putchar_fd_pf(nb + 48, fd);
	return (res);
}
