/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:17:26 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/28 17:06:53 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

long    get_current_time()
{
    struct  timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void    safe_print(t_philosopher *philo, char *msg)
{
    pthread_mutex_lock(philo->shared_data->lock_print);
    if (philo->shared_data->simulation_active)
        printf("%ld %d %s\n", get_current_time(), philo->id, msg);
    pthread_mutex_unlock(philo->shared_data->lock_print);
}
void *monitor_death(void *arg)
{   
    t_philosopher *philosopher = (t_philosopher *)arg;
    while (1)
    {
        if (philosopher->shared_data->survived_philos == philosopher->shared_data->number_of_philosophers)
        {
            philosopher->shared_data->simulation_active = 0;
            return NULL;
        }
        if (get_current_time() - philosopher->last_meal_time > philosopher->shared_data->time_to_die)
        {
            pthread_mutex_lock(philosopher->shared_data->lock_print);
            if (philosopher->shared_data->simulation_active)
            {
                printf("%ld %d died\n", get_current_time(), philosopher->id);
                philosopher->shared_data->simulation_active = 0;
            }
            pthread_mutex_unlock(philosopher->shared_data->lock_print);
            return NULL;
        }
        usleep(10);
    }
    return NULL;
}

void    even_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->right_fork);
    safe_print(philosopher, "has taken a fork");
    pthread_mutex_lock(philosopher->left_fork);
    safe_print(philosopher, "has taken a fork");
}

void    odd_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->left_fork);
    safe_print(philosopher, "has taken a fork");
    pthread_mutex_lock(philosopher->right_fork);
    safe_print(philosopher, "has taken a fork");
}

void    start_eating(t_philosopher *philosopher)
{
    safe_print(philosopher, "is eating");
    philosopher->last_meal_time = get_current_time();
    philosopher->meals_eaten++;
    usleep(philosopher->shared_data->time_to_eat * 1000);
    philosopher->last_meal_time = get_current_time();
    if (philosopher->meals_eaten ==
        philosopher->shared_data->philosopher_must_eat)
        philosopher->shared_data->survived_philos++;
}

void    *thread_function(void *arg)
{
    t_philosopher        *philo;
    pthread_t       monitor_thread;
    
    philo = (t_philosopher *)arg;
    pthread_create(&monitor_thread, NULL, monitor_death, philo);
    pthread_detach(monitor_thread);
    philo->last_meal_time = get_current_time();
    while (philo->shared_data->simulation_active)
    {
        if (philo->id % 2 == 0)
            even_pick_fork(philo);
        else
            odd_pick_fork(philo);
        start_eating(philo);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        safe_print(philo, "is sleeping");
        usleep(philo->shared_data->time_to_sleep * 1000);
        safe_print(philo, "is thining");
    }
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    return NULL;
}
void    thread_creation(t_shared *shared_data)
{
    int i;

    i = 0;
    while (i < shared_data->number_of_philosophers)
    {
        if (pthread_create(&shared_data->philos[i].threads, NULL, thread_function, &shared_data->philos[i]) != 0)
        {
            printf("pthread_create failed");//fix
            //Free all
            exit(1);
        }
        i++;
    }
}

void    philosopher_init(t_shared *shared_data)
{
    int             i;
    t_philosopher   *philosopher;

    philosopher = shared_data->philos;
    i = 0;
    while (i < shared_data->number_of_philosophers)
    {
        philosopher[i].id = i + 1;
        philosopher[i].meals_eaten = 0;
        philosopher[i].last_meal_time = 0;
        philosopher[i].left_fork = &shared_data->forks[i];
        philosopher[i].right_fork = &shared_data->forks[(i + 1) % shared_data->number_of_philosophers];
        philosopher[i].shared_data = shared_data;
        i++;
    }
}


/*void thread_init(t_shared *shared)
{
    int i;
    t_philosopher philo[shared->number_of_philosophers];
    pthread_mutex_t forks[shared->number_of_philosophers];
    pthread_mutex_t print_lock;

    shared->philos = philo;
    shared->forks = forks;
    shared->lock_print = &print_lock;
    i = 0;
    while (i < shared->number_of_philosophers)
        pthread_mutex_init(&shared->forks[i++], NULL);
    pthread_mutex_init(shared->lock_print, NULL);
    philosopher_init(shared);
    thread_creation(shared);
    i = 0;
    while (i < shared->number_of_philosophers)
        pthread_join(shared->philos[i++].threads, NULL);
    i = 0;
    while (i < shared->number_of_philosophers)
    {
        pthread_mutex_destroy(&shared->forks[i]);
        i++;
    }
    pthread_mutex_destroy(shared->lock_print);
}*/

void thread_init(t_shared *shared)
{
    int i;

    shared->philos = malloc(sizeof(t_philosopher) * shared->number_of_philosophers);
    shared->forks = malloc(sizeof(pthread_mutex_t) * shared->number_of_philosophers);
    shared->lock_print = malloc(sizeof(pthread_mutex_t));
    shared->mutex_survived = malloc(sizeof(pthread_mutex_t));

    pthread_mutex_init(shared->lock_print, NULL);
    pthread_mutex_init(shared->mutex_survived, NULL);

    i = 0;
    while (i < shared->number_of_philosophers)
        pthread_mutex_init(&shared->forks[i++], NULL);

    philosopher_init(shared);
    thread_creation(shared);

    i = 0;
    while (i < shared->number_of_philosophers)
        pthread_join(shared->philos[i++].threads, NULL);

    i = 0;
    while (i < shared->number_of_philosophers)
        pthread_mutex_destroy(&shared->forks[i++]);

    pthread_mutex_destroy(shared->lock_print);
    pthread_mutex_destroy(shared->mutex_survived);

    free(shared->philos);
    free(shared->forks);
    free(shared->lock_print);
    free(shared->mutex_survived);
}


void    shared_data_init(t_shared *shared, char **argv)
{
    shared->simulation_active = 1;
    shared->survived_philos = 0;
    shared->number_of_philosophers = ft_atoi(argv[1]);
    shared->time_to_die = ft_atoi(argv[2]);
    shared->time_to_eat = ft_atoi(argv [3]);
    shared->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        shared->philosopher_must_eat = ft_atoi(argv[5]);
    else 
        shared->philosopher_must_eat = -1;
}
int main(int argc, char **argv)
{
    t_shared        shared_data;

    check_args(argc, argv);
    shared_data_init(&shared_data, argv);
    if (shared_data.number_of_philosophers == 1)
    {
        printf("%ld 1 has taken a fork\n", get_current_time());
        usleep(shared_data.time_to_die * 1000);
        printf("%ld 1 died\n", get_current_time());
        return (0);
    }
    thread_init(&shared_data);
    return (0);
}
