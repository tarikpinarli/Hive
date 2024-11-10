/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:32:17 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/10 18:12:31 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	res;

	res = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	res = 48 + (n % 10);
	n = n / 10;
	if (n != 0)
		ft_putnbr_fd(n, fd);
	write (fd, &res, 1);
}

/*int	main(void)
{
	int	nb;

	nb = 2147483647;
	ft_putnbr_fd(nb, 1);
	printf("\n%d", INT_MAX);
	return (0);
}*/
