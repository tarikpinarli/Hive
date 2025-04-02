/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:17:26 by tpinarli          #+#    #+#             */
/*   Updated: 2025/04/02 12:56:04 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    unlock_all(t_shared *shared)
{
    int i;

    i = 0;
    while (i < shared->philo_no)
        pthread_mutex_unlock(&shared->forks[i++]);
    pthread_mutex_unlock(shared->last_meal_mutex);
    pthread_mutex_unlock(shared->sim_mutex);
    pthread_mutex_unlock(shared->mutex_survived);
    pthread_mutex_unlock(shared->lock_print);
}

void    destroy_all(t_shared *shared)
{
    int i;

    i = 0;
    while (i < shared->philo_no)
        pthread_mutex_destroy(&shared->forks[i++]);
    pthread_mutex_destroy(shared->lock_print);
    pthread_mutex_destroy(shared->mutex_survived);
    pthread_mutex_destroy(shared->sim_mutex);
    pthread_mutex_destroy(shared->last_meal_mutex);
}

void increment_survived(t_shared *shared)
{
    pthread_mutex_lock(shared->mutex_survived);
    shared->survived_philos++;
    pthread_mutex_unlock(shared->mutex_survived);
}

int get_survived(t_shared *shared)
{
    int count;
    pthread_mutex_lock(shared->mutex_survived);
    count = shared->survived_philos;
    pthread_mutex_unlock(shared->mutex_survived);
    return count;
}

int is_sim_active(t_shared *shared)
{
    int result;
    pthread_mutex_lock(shared->sim_mutex);
    result = shared->sim_active;
    pthread_mutex_unlock(shared->sim_mutex);
    return result;
}

long get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
long    get_last_meal_time(t_shared *shared)
{
    long    time;
    
    pthread_mutex_lock(shared->last_meal_mutex);
    time = get_current_time();
    pthread_mutex_unlock(shared->last_meal_mutex);
    return(time);
}

void safe_print(t_philosopher *philo, char *msg)
{
    pthread_mutex_lock(philo->shared->lock_print);
    if (is_sim_active(philo->shared))
        printf("%ld %d %s\n", get_current_time(), philo->id, msg);
    pthread_mutex_unlock(philo->shared->lock_print);
}

void *monitor_death(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    while (1)
    {
        if (get_current_time() - philo->last_meal > philo->shared->time_to_die)
        {
            pthread_mutex_lock(philo->shared->lock_print);
            if (is_sim_active(philo->shared))
                printf("%ld %d died\n", get_current_time(), philo->id);
            pthread_mutex_lock(philo->shared->sim_mutex);
            philo->shared->sim_active = 0;
            pthread_mutex_unlock(philo->shared->sim_mutex);
            pthread_mutex_unlock(philo->shared->lock_print);
            pthread_mutex_unlock(philo->left_fork);
            pthread_mutex_unlock(philo->right_fork);
            return (NULL);
        }
        if (get_survived(philo->shared) >= philo->shared->philo_no)
        {
            pthread_mutex_lock(philo->shared->sim_mutex);
            philo->shared->sim_active = 0;
            pthread_mutex_unlock(philo->shared->sim_mutex);
            return NULL;
        }
    }
    return NULL;
}

void even_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->right_fork);
    safe_print(philosopher, "has taken a fork");
    pthread_mutex_lock(philosopher->left_fork);
    safe_print(philosopher, "has taken a fork");
}

void odd_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->left_fork);
    safe_print(philosopher, "has taken a fork");
    pthread_mutex_lock(philosopher->right_fork);
    safe_print(philosopher, "has taken a fork");
}

void start_eating(t_philosopher *philosopher)
{
    if (is_sim_active(philosopher->shared))
    {
        safe_print(philosopher, "is eating");
        philosopher->last_meal = get_last_meal_time(philosopher->shared);
        philosopher->meals_eaten++;
        usleep(philosopher->shared->time_to_eat * 1000);
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);
        philosopher->last_meal = get_last_meal_time(philosopher->shared);
        if (philosopher->meals_eaten == philosopher->shared->must_eat)
            increment_survived(philosopher->shared);
    }
}

void *thread_function(void *arg)
{
    t_philosopher *philo;
    pthread_t monitor;

    philo = (t_philosopher *)arg;
    philo->last_meal = get_last_meal_time(philo->shared);
    pthread_create(&monitor, NULL, monitor_death, philo);
    pthread_detach(monitor);
    while (is_sim_active(philo->shared))
    {
        if (philo->id % 2 == 0 && is_sim_active(philo->shared))
            even_pick_fork(philo);
        else if (is_sim_active(philo->shared))
            odd_pick_fork(philo);
        start_eating(philo);
        safe_print(philo, "is sleeping");
        usleep(philo->shared->time_to_sleep * 1000);
        safe_print(philo, "is thinking");
    }
    unlock_all(philo->shared);
    return NULL;
}

void thread_creation(t_shared *shared)
{
    int i = 0;
    while (i < shared->philo_no)
    {
        if (pthread_create(&shared->philos[i].threads, NULL,
            thread_function, &shared->philos[i]) != 0)
        {
            printf("pthread_create failed\n");
            free_all(shared);
            exit(1);
        }
        i++;
    }
}

void philosopher_init(t_shared *shared)
{
    int i = 0;
    t_philosopher *philo = shared->philos;

    while (i < shared->philo_no)
    {
        philo[i].id = i + 1;
        philo[i].meals_eaten = 0;
        philo[i].last_meal = 0;
        pthread_mutex_init(&philo[i].meal_mutex, NULL);
        philo[i].left_fork = &shared->forks[i];
        philo[i].right_fork = &shared->forks[(i + 1) % shared->philo_no];
        philo[i].shared = shared;
        i++;
    }
}

void thread_init(t_shared *shared)
{
    int i;

    shared->philos = malloc(sizeof(t_philosopher) * shared->philo_no);
    shared->forks = malloc(sizeof(pthread_mutex_t) * shared->philo_no);
    pthread_mutex_init(&shared->print_mutex, NULL);
    pthread_mutex_init(&shared->sim_mutex, NULL);
    pthread_mutex_init(&shared->philo.meal_mutex, NULL);
    pthread_mutex_init(shared->last_meal_mutex, NULL);
    i = 0;
    while (i < shared->philo_no)
        pthread_mutex_init(&shared->forks[i++], NULL);

    philosopher_init(shared);
    thread_creation(shared);

    i = 0;
    while (i < shared->philo_no)
        pthread_join(shared->philos[i++].threads, NULL);
    destroy_all(shared);
    free_all(shared);
}

void shared_data_init(t_shared *shared, char **argv)
{
    shared->sim_active = 1;
    shared->survived_philos = 0;
    shared->philo_no = ft_atoi(argv[1]);
    shared->time_to_die = ft_atoi(argv[2]);
    shared->time_to_eat = ft_atoi(argv[3]);
    shared->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        shared->must_eat = ft_atoi(argv[5]);
    else
        shared->must_eat = -1;
}

int main(int argc, char **argv)
{
    t_shared shared_data;

    check_args(argc, argv);
    shared_data_init(&shared_data, argv);
    thread_init(&shared_data);
    return (0);
}
