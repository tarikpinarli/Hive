/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:05:14 by tpinarli          #+#    #+#             */
/*   Updated: 2025/04/01 16:47:10 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    free_all(t_shared *shared)
{
    if (shared->philos)
        free(shared->philos);
    if (shared->forks)
        free(shared->forks);
    if (shared->lock_print)
        free(shared->lock_print);
    if (shared->mutex_survived)
        free(shared->mutex_survived);
    if (shared->sim_mutex)
        free(shared->sim_mutex);
    if (shared->last_meal_mutex)
        free(shared->last_meal_mutex);
}