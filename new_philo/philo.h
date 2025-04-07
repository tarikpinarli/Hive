#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				num_philo;
	long			time_to_die;
	long			time_to_eat;
	int				meals_to_eat;
	long			time_to_sleep;
	long			last_meal;
	struct s_shared	*shared;
	bool			philo_deid;
	bool			philo_survived;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philo;

typedef struct s_shared
{
	int				num_philo;
	int				num_forks;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	long			sim_start_time;
	int				philo_created;
	pthread_mutex_t	shared_state_lock;
	bool			a_philo_is_dead;
	bool			print_lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	monitor;
	pthread_t		monitor_thread;
	pthread_mutex_t	print_mutex;
	t_philo			*philo;
}	t_shared;

int	check_args(int argc, char **argv);
long	ft_atol(const char *str);
void    free_all(t_shared *shared);

#endif