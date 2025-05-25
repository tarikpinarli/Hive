/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:27:23 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 20:53:56 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
    start_simulation(table);
	arena_destroy(arena);
	return (0);
}

