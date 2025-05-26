/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:09:12 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/26 16:16:58 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	philo_is_full(t_philo *philo)
{
	bool	is_full;

	pthread_mutex_lock(&philo->table->status_mutex);
	is_full = (philo->meals_to_eat == philo->table->required_meals);
	pthread_mutex_unlock(&philo->table->status_mutex);
	return (is_full);
}

static long	calculate_think_time(t_philo *philo)
{
	long	margin;
	long	think_time;

	margin = philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep);
	if (margin <= 0)
		think_time = 0;
	else if (margin <= 10)
		think_time = 1;
	else
		think_time = margin / 2;
	return (think_time);
}

void	philo_think(t_philo *philo)
{
	long	think_time;

	if (table_death_check(philo) || monitor_philo_death(philo))
		return ;
	if (philo_is_full(philo))
		return ;
	think_time = calculate_think_time(philo);
	if (think_time > 0)
	{
		safe_print(philo, "is thinking");
		safe_sleep(philo, think_time);
	}
}


