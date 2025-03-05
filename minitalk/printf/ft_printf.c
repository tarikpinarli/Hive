/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:12:22 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/12 12:48:22 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_handle(char f, char ch, va_list ptr);

int	ft_printf(const char *first, ...)
{
	va_list	ptr;
	int		count;
	size_t	i;

	va_start (ptr, first);
	count = 0;
	i = 0;
	if (!first)
		return (-1);
	while (first[i])
	{
		if (first[i] == '%')
		{
			count += format_handle(first[i], first[i + 1], ptr);
			i++;
		}
		else
			count += ft_putchar_fd_pf(first[i], 1);
		i++;
	}
	va_end(ptr);
	return (count);
}

int	format_handle(char f, char ch, va_list ptr)
{
	int	count;

	count = 0;
	if (ch == 's')
		count += ft_putstr_fd_pf(va_arg(ptr, char *), 1);
	else if (ch == 'c')
		count += ft_putchar_fd_pf(va_arg(ptr, int), 1);
	else if (ch == 'd' || ch == 'i')
		count += ft_putnbr_fd_pf(va_arg(ptr, int), 1);
	else if (ch == 'p')
		count += ft_puthex_fd(va_arg(ptr, void *), 1);
	else if (ch == 'u')
		count += ft_putunsigned_fd(va_arg(ptr, unsigned int), 1);
	else if (ch == 'x')
		count += ft_putlowerhex(va_arg(ptr, unsigned int), 1);
	else if (ch == 'X')
		count += ft_putupperhex(va_arg(ptr, unsigned int), 1);
	else if (ch == '%')
		count += ft_putchar_fd_pf('%', 1);
	else
	{
		count += ft_putchar_fd_pf(f, 1);
		count += ft_putchar_fd_pf(ch, 1);
	}
	return (count);
}
