/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:09:03 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 20:09:30 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_philos(t_arena *arena, t_table *table)
{
	int	i;
	t_philo *p;

	table->philo = arena_alloc(arena, sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		return (1);
	i = 0;
	while (i < table->num_philo)
	{
		p = &table->philo[i];
		p->id = i + 1;
		p->num_philo = table->num_philo;
		p->time_to_die = table->time_to_die;
		p->time_to_eat = table->time_to_eat;
		p->time_to_sleep = table->time_to_sleep;
		p->meals_to_eat = table->required_meals;
		p->last_meal_time = 0;
		p->table = table;
		p->i_am_dead = false;
		p->i_am_full = false;
		p->right_fork = &table->forks[i];
		p->left_fork = &table->forks[(i + 1) % table->num_philo];
		i++;
	}
	return (0);
}