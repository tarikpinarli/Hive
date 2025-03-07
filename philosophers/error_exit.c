/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:30:34 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/07 16:53:37 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    print_err_exit(char *str)
{
    printf("%s", str);
    exit(1);
}

void    print_err_free_exit(t_data *data, pthread_t *threads, pthread_mutex_t *forks)
{
    if (data)
        free(data);
    if (threads)
        free(threads);
    if (forks)
        free(forks);
    print_err_exit("Malloc failed in main.\n");
}
