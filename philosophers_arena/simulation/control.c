/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:43:59 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 21:01:07 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				philo_routine, &table->philo[i]) != 0)
		{
			printf("Error: Failed to create thread for philosopher %d\n", i + 1);
			table->num_philo = i;
			while (--i >= 0)
				pthread_join(table->philo[i].thread, NULL);
			return (1);
		}
		table->philo_created = i + 1;
		i++;
	}
	return (0);
}

int	create_monitor_thread(t_table *table)
{
    int i;

	if (pthread_create(&table->monitor_thread, NULL,
			monitor_death, table) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		i = table->philo_created;
		while (i >= 0)
		{
			i--;
			pthread_join(table->philo[i].thread, NULL);	
		}
		return (1);
	}
	return (0);
}

void	join_philo_threads(t_table *table)
{
	int	i;

    i = 0;
	while (i < table->philo_created)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			printf("Error: Failed to join thread for philosopher %d\n", i + 1);
		i++;
	}
}

void	join_monitor_thread(t_table *table)
{
	if (pthread_join(table->monitor_thread, NULL) != 0)
		printf("Error: Failed to join monitor thread\n");
}

void	start_simulation(t_table *table)
{
	if (create_philo_threads(table) != 0)
		return;
	if (create_monitor_thread(table) != 0)
	{
		join_philo_threads(table);
		return;
	}
	join_monitor_thread(table);
	join_philo_threads(table);
}