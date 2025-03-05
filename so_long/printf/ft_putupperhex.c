/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putupperhex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:38:39 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/12 12:47:18 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putupperhex(unsigned int nb, int fd)
{
	int		count;
	int		i;
	char	buffer[17];
	char	*hex;

	hex = "0123456789ABCDEF";
	i = 0;
	count = 0;
	if (nb == 0)
		return (ft_putchar_fd_pf('0', fd));
	while (nb > 0)
	{
		buffer[i++] = hex[nb % 16];
		nb /= 16;
	}
	buffer[i] = '\0';
	while (i--)
		count += ft_putchar_fd_pf(buffer[i], fd);
	return (count);
}
