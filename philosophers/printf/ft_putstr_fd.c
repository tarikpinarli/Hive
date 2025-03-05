/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:22:03 by tpinarli          #+#    #+#             */
/*   Updated: 2024/12/03 13:48:18 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	count;
	int	ret;

	ret = 0;
	count = 0;
	if (s == NULL)
		return (write(1, "(null)", 6));
	while (*s)
	{
		ret = write(fd, s++, 1);
		if (ret < 0)
			return (-1);
		count += ret;
	}
	return (count);
}
