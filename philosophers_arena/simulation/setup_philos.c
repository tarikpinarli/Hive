/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:02:51 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/26 16:24:25 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	monitor_philo_death(t_philo *philo)
{
	long	now;
	long	time_since_last_meal;

	now = get_current_time_microseconds();
	time_since_last_meal = now - philo->last_meal_time;
	if (time_since_last_meal < philo->time_to_die * 1000)
		return (0);
	pthread_mutex_lock(&philo->table->status_mutex);
	if (philo->table->a_philo_is_dead == false)
	{
		philo->table->a_philo_is_dead = true;
		philo->table->print = false;
		philo->i_am_dead = true;
		pthread_mutex_unlock(&philo->table->status_mutex);
		pthread_mutex_lock(&philo->table->print_mutex);
		printf("%ld %d died\n",
			(now - philo->table->simul_start_time) / 1000, philo->id);
		pthread_mutex_unlock(&philo->table->print_mutex);
	}
	else
		pthread_mutex_unlock(&philo->table->status_mutex);
	return (1);
}


int	table_death_check(t_philo *philo)
{
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(&table->status_mutex);
	if (table->a_philo_is_dead)
	{
		pthread_mutex_unlock(&table->status_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->status_mutex);
	return (1);
}

void	wait_thread_creations(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->status_mutex);
		if (table->philo_created == table->num_philo)
		{
			pthread_mutex_unlock(&table->status_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->status_mutex);
		usleep(1000);
	}
}

void	*setup_philos(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_thread_creations(philo->table);
	pthread_mutex_lock(&philo->table->status_mutex);
	philo->last_meal_time = get_current_time_microseconds();
	pthread_mutex_unlock(&philo->table->status_mutex);
	if (philo->id % 2 != 0)
	{
		safe_print(philo, "is thinking");
		usleep(5000);
	}
	philo_routine(philo);
	return (NULL);
}
