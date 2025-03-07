/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:01 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/07 16:54:00 by tpinarli         ###   ########.fr       */
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

typedef struct s_data
{
    int             id;
    int             number_of_philosophers;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             philosopher_must_eat;
    int             meals_eaten;
    long            last_meal_time;
    int             survived;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}   t_data;

int	ft_atoi(const char *str);
void	check_args(int argc, char **argv);

//Error
void    print_err_exit(char *str);
void    print_err_free_exit(t_data *data, pthread_t *threads, pthread_mutex_t *forks);

#endif