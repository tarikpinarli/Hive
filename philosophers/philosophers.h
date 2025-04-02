/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:40:01 by tpinarli          #+#    #+#             */
/*   Updated: 2025/04/02 12:49:37 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h> //for sleep
# include <stdio.h> //delete later
# include <stdbool.h> //bool
# include <sys/time.h>

typedef struct s_shared t_shared;

typedef struct s_philosopher
{
    pthread_t       thread;             // Philosopher thread
    int             id;                 // Philosopher number (1 to N)
    int             meals_eaten;        // Number of meals eaten
    long            last_meal;          // Timestamp of last meal
    pthread_mutex_t meal_mutex;         // Protects access to last_meal

    pthread_mutex_t *left_fork;         // Pointer to left fork
    pthread_mutex_t *right_fork;        // Pointer to right fork

    struct s_shared *shared;            // Pointer to shared state
}   t_philosopher;


typedef struct s_shared
{
    int             philo_no;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;

    long            start_time;         // For tracking simulation timing

    int             sim_active;         // 1 if simulation still running
    pthread_mutex_t sim_mutex;          // Protects sim_active

    int             survived_philos;    // Philos who reached must_eat
    pthread_mutex_t survived_mutex;     // Protects survived_philos

    pthread_mutex_t print_mutex;        // Controls stdout printing
    pthread_mutex_t *forks;             // Array of fork mutexes

    t_philosopher   *philos;            // Array of philosophers
}   t_shared;


int	ft_atoi(const char *str);
void	check_args(int argc, char **argv);

//Error
void    print_err_exit(char *str);
//free
void    free_all(t_shared *shared);
#endif