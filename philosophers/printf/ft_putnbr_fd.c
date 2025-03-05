/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:32:17 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/28 15:11:53 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	dig_count(int n);

int	ft_putnbr_fd(int n, int fd)
{
	char	res;
	int		count;
	int		nb;

	count = 0;
	res = 0;
	nb = n;
	if (n == 0)
		return (ft_putchar_fd('0', fd));
	if (nb == -2147483648)
		return (write(fd, "-2147483648", 11));
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	res = 48 + (nb % 10);
	nb = nb / 10;
	if (nb != 0)
		ft_putnbr_fd(nb, fd);
	write (fd, &res, 1);
	count = dig_count(n);
	return (count);
}

int	dig_count(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
