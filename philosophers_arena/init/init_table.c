/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:06:39 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 20:12:24 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_invalid_input(t_table *table, char **argv)
{
	if (table->num_philo <= 0)
		printf("Error: Number of philosophers must be greater than 0.\n");
	else if (table->time_to_die <= 0)
		printf("Error: Time to die must be greater than 0.\n");
	else if (table->time_to_eat <= 0)
		printf("Error: Time to eat must be greater than 0.\n");
	else if (table->time_to_sleep <= 0)
		printf("Error: Time to sleep must be greater than 0.\n");
	else if (argv[5] && table->required_meals <= 0)
		printf("Error: Number of required meals must be greater than 0.\n");
	else if (table->num_philo >  INT_MAX
            || table->time_to_die > INT_MAX
            || table->time_to_eat > INT_MAX
			|| table->time_to_sleep > INT_MAX
            || (argv[5] && table->required_meals > INT_MAX))
		printf("Error: One or more arguments exceed INT_MAX.\n");
	else
		return (0);
	return (1);
}

void	fill_table_from_args(t_table *table, char **argv)
{
	table->num_philo = ft_atoi(argv[1]);
	table->num_forks = table->num_philo;
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->required_meals = ft_atoi(argv[5]);
    else
        table->required_meals = -1;
}

int	init_table_struct(t_arena *arena, t_table **table_ptr, char **argv)
{
	t_table	*table;

	table = arena_alloc(arena, sizeof(t_table));
	if (!table)
		return (1);
	*table_ptr = table;
	fill_table_from_args(table, argv);
	if (check_invalid_input(table, argv))
		return (1);
	table->simul_start_time = get_current_time_microseconds();
	table->philo_created = 0;
	table->philo_die = false;
	table->print = true;
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (1);
	table->print_mutex_init = 0;
	if (pthread_mutex_init(&table->status_mutex, NULL) != 0)
		return (1);
	table->status_mutex_init = 0;
	if (pthread_mutex_init(&table->monitor, NULL) != 0)
		return (1);
	table->monitor_init = 0;
	return (0);
}