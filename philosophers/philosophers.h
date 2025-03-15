/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:01 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/15 12:55:38 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include "printf/ft_printf.h"
# include <unistd.h> //for sleep
# include <stdio.h> //delete later
# include <stdbool.h> //bool
# include <sys/time.h>

typedef struct s_shared t_shared;

typedef struct s_philosopher
{
    pthread_t       threads;
    int             id;
    int             meals_eaten;
    long            last_meal_time;
    int             survived;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_shared        *shared_data;
}   t_philosopher;

typedef struct s_shared
{
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             philosopher_must_eat;
    int             simulation_active;
    pthread_mutex_t *forks;
    t_philosopher   *philos;
}   t_shared;

int	ft_atoi(const char *str);
void	check_args(int argc, char **argv);

//Error
void    print_err_exit(char *str);
//void    print_err_free_exit(t_shared *shared_data, t_philosopher *philosopher);
//void    free_all(t_shared *shared_data, t_philosopher *philosopher);

#endif