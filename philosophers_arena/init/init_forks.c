/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:08:00 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 20:08:22 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	init_forks(t_arena *arena, t_table *table)
{
	int	i;

	table->forks = arena_alloc(arena, sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->forks)
		return (1);

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}