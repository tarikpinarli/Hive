/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:30:34 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/15 12:31:49 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_err_exit(char *str)
{
    printf("%s", str);
    exit(1);
}

/*void    print_err_free_exit(t_shared *shared, t_philosopher *philosopher)
{
    if (shared)
    {
        if (shared->forks)
            free(shared->forks);
        if (shared->threads)
            free(shared->threads);
        free(shared);
    }
    if (philosopher)
        free(philosopher);
    print_err_exit("Malloc failed in main.\n");
}*/

