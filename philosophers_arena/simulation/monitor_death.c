/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:53:38 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/26 16:07:22 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	check_all_full(t_table *table)
{
	int	index;
	int	full_count;

	index = 0;
	full_count = 0;

	pthread_mutex_lock(&table->status_mutex);
	while (index < table->num_philo)
	{
		if (table->philo[index].i_am_full)
			full_count++;
		index++;
	}
	if (full_count == table->num_philo)
	{
		table->a_philo_is_dead = true;
		table->print = false;
	}
	pthread_mutex_unlock(&table->status_mutex);
}

static bool	check_if_dead(t_table *table, t_philo *philo)
{
	long	now;
	long	time_since_last_meal;

	now = get_current_time_microseconds();
	time_since_last_meal = now - philo->last_meal_time;
	pthread_mutex_lock(&table->status_mutex);
	if (table->a_philo_is_dead)
	{
		pthread_mutex_unlock(&table->status_mutex);
		return (true);
	}
	if (time_since_last_meal >= philo->time_to_die * 1000)
	{
		table->a_philo_is_dead = true;
		table->print = false;
		pthread_mutex_unlock(&table->status_mutex);

		pthread_mutex_lock(&table->print_mutex);
		printf("%ld %d died\n",
			(now - table->simul_start_time) / 1000,
			philo->id);
		pthread_mutex_unlock(&table->print_mutex);
		return (true);
	}
	pthread_mutex_unlock(&table->status_mutex);
	return (false);
}

void	*monitor_death(void *arg)
{
	t_table	*table;
	int		index;
	t_philo	*philo;

	table = (t_table *)arg;

	while (1)
	{
		usleep(1000);
		index = 0;
		while (index < table->num_philo)
		{
			philo = &table->philo[index];
			if (check_if_dead(table, philo))
				return (NULL);
			index++;
		}
		check_all_full(table);
	}
	return (NULL);
}
