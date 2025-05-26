/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:22:22 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/26 16:25:19 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	is_simulation_stopped(t_philo *philo)
{
	return (table_death_check(philo) || monitor_philo_death(philo));
}

static void	mark_philo_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->status_mutex);
	philo->i_am_full = true;
	pthread_mutex_unlock(&philo->table->status_mutex);
}

static bool	philo_routine_cycle(t_philo *philo)
{
	if (is_simulation_stopped(philo))
		return (true);
	philo_think(philo);
	if (is_simulation_stopped(philo))
		return (true);
	//philo_eat(philo);
	if (philo->meals_to_eat == 0)
	{
		mark_philo_full(philo);
		return (true);
	}
	if (is_simulation_stopped(philo))
		return (true);
	//philo_sleep(philo);
	return (false);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_routine_cycle(philo))
			break ;
	}
	return (NULL);
}



