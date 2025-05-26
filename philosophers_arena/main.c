/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:27:23 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/26 15:50:14 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, const char *message)
{
	long	timestamp;
	bool	is_dead;
	bool	can_print;

	pthread_mutex_lock(&philo->table->status_mutex);
	is_dead = philo->table->a_philo_is_dead;
	can_print = philo->table->print;
	pthread_mutex_unlock(&philo->table->status_mutex);
	if (is_dead || !can_print)
		return ;
	pthread_mutex_lock(&philo->table->print_mutex);
	timestamp = (get_current_time_microseconds() - philo->table->simul_start_time) / 1000;
	printf("%ld %d %s\n", timestamp, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_mutex);
}


int	single_philosopher(t_philo *philo)
{
	safe_print(philo, "is thinking");
	pthread_mutex_lock(philo->right_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_unlock(philo->right_fork);
	usleep(philo->time_to_die * 1000);
	return (1);
}

int	main(int argc, char **argv)
{
	t_arena	*arena;
	t_table	*table;

	if (input_check(argc, argv) == 1)
		return (1);

	arena = arena_init(10000);
	if (!arena)
	{
		printf("Error: Arena allocation failed.\n");
		return (1);
	}
	if (table_init(arena, &table, argv) == 1)
	{
		arena_destroy(arena);
		return (1);
	}
	if (table->num_philo == 1)
		return (single_philosopher(table->philo));
    start_simulation(table);
	arena_destroy(arena);
	return (0);
}

