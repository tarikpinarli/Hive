/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlowerhex_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:46:20 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/12 12:46:27 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putlowerhex(unsigned int nb, int fd)
{
	const char	*hex;
	char		buffer[17];
	int			i;
	int			count;

	count = 0;
	i = 0;
	hex = "0123456789abcdef";
	if (nb == 0)
		return (ft_putchar_fd_pf('0', fd));
	while (nb > 0)
	{
		buffer[i++] = hex[nb % 16];
		nb = nb / 16;
	}
	buffer[i] = '\0';
	while (i--)
		count += ft_putchar_fd_pf(buffer[i], fd);
	return (count);
}
