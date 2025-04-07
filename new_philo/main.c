
#include "philo.h"

long get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	survived_check(t_shared *shared)
{
	int	num_philo_survived;
	int	i;

	num_philo_survived = 0;
	i = 0;
	pthread_mutex_lock(&shared->shared_state_lock);
	while (i < shared->num_philo)
	{
		if (shared->philo[i].philo_survived == true)
			num_philo_survived++;
		i++;
	}
	if (num_philo_survived == shared->num_philo)
	{
		shared->a_philo_is_dead = true;
		shared->print_lock = false;
		pthread_mutex_unlock(&shared->shared_state_lock);
		return ;
	}
	pthread_mutex_unlock(&shared->shared_state_lock);
}

static inline int	detect_dead_philosopher(t_shared *shared, int i)
{
	long	current_time;

	current_time = get_current_time();
	pthread_mutex_lock(&shared->shared_state_lock);
	if (shared->a_philo_is_dead)
	{
		pthread_mutex_unlock(&shared->shared_state_lock);
		return (1);
	}
	if ((current_time - shared->philo[i].last_meal) >= \
		shared->philo[i].time_to_die)
	{
		shared->a_philo_is_dead = true;
		shared->print_lock = false;
		pthread_mutex_unlock(&shared->shared_state_lock);
		pthread_mutex_lock(&shared->print_mutex);
		printf("%ld %d died\n",
			(current_time - shared->sim_start_time),
			shared->philo[i].id);
		pthread_mutex_unlock(&shared->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&shared->shared_state_lock);
	return (0);
}

void	*monitor_death(void *arg)
{
	t_shared	*shared;
	int		i;

	shared = (t_shared *)arg;
	while (1)
	{
		i = 0;
		while (i < shared->num_philo)
		{
			if (detect_dead_philosopher(shared, i) == 1)
				return (NULL);
			i++;
		}
		survived_check(shared);
        usleep(1000);
	}
	return (NULL);
}

void    monitor_creation(t_shared *shared)
{
    int i;

    i = 0;
    if (pthread_create(&shared->monitor_thread, NULL, monitor_death, shared) != 0)
	{
		printf("Monitor creation failed.\n");
		while (i > 0)
			pthread_join(shared->philo[--i].thread, NULL);
		return ;
	}
}

void    wait_creation_complete(t_philo *philo)
{
    while (1)
	{
		pthread_mutex_lock(&philo->shared->shared_state_lock);
		if (philo->shared->philo_created == philo->shared->num_philo)
		{
			pthread_mutex_unlock(&philo->shared->shared_state_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->shared->shared_state_lock);
		usleep(1000);
	}
}

bool	check_death(t_philo *philo)
{
	long	current_time;

	current_time = get_current_time();
	if ((current_time - philo->last_meal) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->shared->shared_state_lock);
		if (!philo->shared->a_philo_is_dead)
		{
			philo->shared->a_philo_is_dead = true;
			philo->shared->print_lock = false;
			philo->philo_deid = true;
			pthread_mutex_unlock(&philo->shared->shared_state_lock);
			pthread_mutex_lock(&philo->shared->print_mutex);
			printf("%ld %d died\n", (current_time - \
				philo->shared->sim_start_time) / 1000, philo->id);
			pthread_mutex_unlock(&philo->shared->print_mutex);
		}
		else
			pthread_mutex_unlock(&philo->shared->shared_state_lock);
		return (true);
	}
	return (false);
}

void safe_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared->print_mutex);
	pthread_mutex_lock(&philo->shared->shared_state_lock);
	if (philo->shared->a_philo_is_dead || philo->shared->print_lock == false)
	{
		pthread_mutex_unlock(&philo->shared->shared_state_lock);
		pthread_mutex_unlock(&philo->shared->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->shared->shared_state_lock);
	printf("%ld %d %s\n", get_current_time() - philo->shared->sim_start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->shared->print_mutex);
}

void even_pick_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    safe_print(philo, "has taken a fork");
    pthread_mutex_lock(philo->left_fork);
    safe_print(philo, "has taken a fork");
}

void odd_pick_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    safe_print(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    safe_print(philo, "has taken a fork");
}

//burada kaldin 06.04.2025 20.51
bool	safe_death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->shared_state_lock);
	if (philo->shared->a_philo_is_dead)
	{
		pthread_mutex_unlock(&philo->shared->shared_state_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->shared->shared_state_lock);
	return (false);
}

bool smart_eating(t_philo *philo)
{
    int slept;

	slept = 0;
	safe_print(philo, "is eating");
    while (slept < philo->time_to_eat)
    {
        if (philo->shared->a_philo_is_dead)
			return (false);
        usleep(1000);
        slept += 1000;
    }
	pthread_mutex_lock(&philo->shared->shared_state_lock);
	philo->last_meal = get_current_time();
	philo->meals_to_eat--;
	pthread_mutex_unlock(&philo->shared->shared_state_lock);
	return (true);
}


void *thread_function(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_creation_complete(philo);
    pthread_mutex_lock(&philo->shared->shared_state_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->shared->shared_state_lock);
	while (1)
	{
		if (philo->id % 2 == 0)
			even_pick_fork(philo);
		else
			odd_pick_fork(philo);
		if (check_death(philo) == true)
			return (NULL);
		if (!smart_eating(philo))
			return (NULL);
		if (philo->meals_to_eat == 0)
		{
			pthread_mutex_lock(&philo->shared->shared_state_lock);
			philo->philo_survived = true;
			pthread_mutex_unlock(&philo->shared->shared_state_lock);
			return (NULL);
		}
		if (check_death(philo) == true)
			return (NULL);
		safe_print(philo, "is sleeping");
		usleep(philo->shared->time_to_sleep * 1000);
		safe_print(philo, "is thinking");
		if (check_death(philo) == true)
			return (NULL);
	}
    return (NULL);
}

void thread_creation(t_shared *shared)
{
    int	i;

	i = 0;
	while (i < shared->num_philo)
	{
		if (pthread_create(&shared->philo[i].thread, NULL, \
			thread_function, &shared->philo[i]) != 0)
		{
			printf("Thread creation failed\n");
			while (i > 0)
				pthread_join(shared->philo[--i].thread, NULL);
			return ;
		}
		i++;
        pthread_mutex_lock(&shared->shared_state_lock);
        shared->philo_created++;
        pthread_mutex_unlock(&shared->shared_state_lock);
	}
}

void philos_data_init(t_shared *shared)
{
    int i;

    shared->philo = malloc(sizeof(t_philo) * shared->num_philo);
    if (!shared->philo)
        free_all(shared);
    i = 0;
    while (i < shared->num_philo)
    {
        shared->philo[i].id = i + 1;
        shared->philo[i].num_philo = shared->num_philo;
        shared->philo[i].time_to_die = shared->time_to_die * 1000;
        shared->philo[i].time_to_eat = shared->time_to_eat * 1000;
        shared->philo[i].meals_to_eat = shared->must_eat;
        shared->philo[i].time_to_sleep = shared->time_to_sleep;
        shared->philo[i].last_meal = get_current_time();
        shared->philo[i].left_fork = &shared->forks[i];
        shared->philo[i].right_fork = &shared->forks[(i + 1) % shared->num_philo];
        shared->philo[i].shared = shared;
        shared->philo[i].philo_deid = false;
		shared->philo[i].philo_survived = false;
        i++;
    }
    pthread_mutex_init(&shared->monitor, NULL);
}

void shared_data_init(t_shared *shared, char **argv)
{
    int i;

	shared->num_philo = ft_atol(argv[1]);
	shared->num_forks = ft_atol(argv[1]);
	shared->time_to_die = ft_atol(argv[2]);
	shared->time_to_eat = ft_atol(argv[3]);
	shared->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
        shared->must_eat = ft_atol(argv[5]);
    else
        shared->must_eat = -1;
    shared->sim_start_time = get_current_time();
    shared->philo_created = 0;
    shared->a_philo_is_dead = false;
    shared->print_lock = true;
    pthread_mutex_init(&shared->print_mutex, NULL);
    pthread_mutex_init(&shared->shared_state_lock, NULL);
    shared->forks = malloc(sizeof(pthread_mutex_t) * shared->num_philo);
    if (!shared->forks)
        free_all(shared);
    i = 0;
    while (i < shared->num_philo)
        pthread_mutex_init(&shared->forks[i++], NULL);
}

void	join_threads(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->num_philo)
	{
		if (pthread_join(shared->philo[i].thread, NULL))
			printf("Failed to join thread for philosopher %d\n", i + 1);
		i++;
	}
}

void	join_monitor(t_shared *shared)
{
	if (pthread_join(shared->monitor_thread, NULL) != 0)
		printf("Failed to join monitor thread\n");
}

int main(int argc, char **argv)
{
    t_shared shared_data;

    if (!check_args(argc, argv))
        return (1);
    shared_data_init(&shared_data, argv);
    philos_data_init(&shared_data);
    thread_creation(&shared_data);
    monitor_creation(&shared_data);
	join_monitor(&shared_data);
	join_threads(&shared_data);
    return (0);
}
