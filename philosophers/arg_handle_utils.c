/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handle_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:40:30 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/28 16:16:30 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return(1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == -1 && (result * sign > 0))
			return (0);
		if (sign == 1 && (result * sign < 0))
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if(argc != 5 && argc != 6)
		print_err_exit("Invalid argument count.\n");
	while(i < argc)
	{
		if (!ft_isdigit(argv[i]))
			print_err_exit("Non digit input.\n");
		i++;
	}
}
