/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:41:56 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 19:54:53 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	long_check(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	if (i > 11)
	{
		return (1);
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	number;
	long	result;

	i = 0;
	sign = 1;
	number = 0;
	if (1 == long_check(str))
		return (-1);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	result = (number * sign);
	return (result);
}