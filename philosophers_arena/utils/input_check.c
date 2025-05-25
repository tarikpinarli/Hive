/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:15:07 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 20:56:09 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	input_check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments.\n");
        printf("Usage: ./philo [number_of_philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep] [meals_required]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("Error: Argument %d contains non-digit characters.\n", i);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
