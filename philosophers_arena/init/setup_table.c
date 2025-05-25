/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 20:10:11 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 20:10:44 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	table_init(t_arena *arena, t_table **table_ptr, char **argv)
{
	if (init_table_struct(arena, table_ptr, argv))
		return (1);
	if (init_forks(arena, *table_ptr))
		return (1);
	if (init_philos(arena, *table_ptr))
		return (1);
	return (0);
}