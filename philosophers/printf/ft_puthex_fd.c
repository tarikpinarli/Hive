/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:22:46 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/28 12:54:59 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_fd(void *ptr, int fd)
{
	uintptr_t		address;
	const char		*hex;
	char			buffer[17];
	int				i;
	int				count;

	address = (uintptr_t)ptr;
	hex = "0123456789abcdef";
	count = 0;
	i = 0;
	if (ptr == 0)
		return (ft_putstr_fd("(nil)", fd));
	while (address > 0)
	{
		buffer[i++] = hex[address % 16];
		address /= 16;
	}
	buffer[i] = '\0';
	count += ft_putstr_fd("0x", fd);
	while (i-- > 0)
		count += ft_putchar_fd(buffer[i], fd);
	return (count);
}
