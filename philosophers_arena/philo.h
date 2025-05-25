/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:27:57 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 20:50:59 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>


typedef struct s_arena
{
    void    *memory;
    size_t   size;
    size_t   offset;
}   t_arena;

struct	s_table;

typedef struct s_philo
{
	int				id;
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	int				meals_to_eat;
	long			time_to_sleep;
	long			last_meal_time;
	struct s_table  *table;
	bool			i_am_dead;
	bool			i_am_full;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	int				num_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				required_meals;
	long			simul_start_time;
	int				philo_created;
	pthread_mutex_t	status_mutex;
	bool			philo_die;
	bool			print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	monitor;
	pthread_t		monitor_thread;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
	int				print_mutex_init;
	int				status_mutex_init;
	int				monitor_init;
}	t_table;

t_arena     *arena_init(size_t size);
void        *arena_alloc(t_arena *arena, size_t size);
void        arena_destroy(t_arena *arena);

// utils
int         input_check(int argc, char **argv);
long        get_current_time_microseconds(void);
long        ft_atoi(const char *str);
// init/
int         init_table_struct(t_arena *arena, t_table **table_ptr, char **argv);
void        fill_table_from_args(t_table *table, char **argv);
int         check_invalid_input(t_table *table, char **argv);
int         init_forks(t_arena *arena, t_table *table);
int         init_philos(t_arena *arena, t_table *table);
int         table_init(t_arena *arena, t_table **table_ptr, char **argv);
// simulation
int		    create_philo_threads(t_table *table);
int		    create_monitor_thread(t_table *table);
void	    join_philo_threads(t_table *table);
void	    join_monitor_thread(t_table *table);
void	    start_simulation(t_table *table);
// routine
void	    *philo_routine(void *arg);
void	    *monitor_death(void *arg);

// Monitor

#endif