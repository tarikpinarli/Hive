/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:17:26 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/26 14:53:26 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosophers.h"

long    get_current_time()
{
    struct  timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void *monitor_death(void *arg)
{   
    t_philosopher *philosopher = (t_philosopher *)arg;
    while (!philosopher->survived && philosopher->shared_data->simulation_active)
    {
        if (get_current_time() - philosopher->last_meal_time > philosopher->shared_data->time_to_die)
        {
            if (philosopher->shared_data->simulation_active && !philosopher->survived)
                printf("%ld %d died\n",get_current_time() , philosopher->id);
            philosopher->shared_data->simulation_active = 0;
            return NULL;
        }
        usleep(1000);
    }
    return NULL;
}

void    even_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->right_fork);
    if (philosopher->shared_data->simulation_active && !philosopher->survived)
        printf("%ld %d has taken a fork\n"
                ,get_current_time() , philosopher->id);
    pthread_mutex_lock(philosopher->left_fork);
    if (philosopher->shared_data->simulation_active && !philosopher->survived)
        printf("%ld %d has taken a fork\n"
                ,get_current_time() , philosopher->id);
}

void    odd_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->left_fork);
    if (philosopher->shared_data->simulation_active && !philosopher->survived)
        printf("%ld %d has taken a fork\n"
                ,get_current_time() , philosopher->id);
    pthread_mutex_lock(philosopher->right_fork);
    if (philosopher->shared_data->simulation_active && !philosopher->survived)
        printf("%ld %d has taken a fork\n"
                ,get_current_time() , philosopher->id);
}

void    start_eating(t_philosopher *philosopher)
{
    if (philosopher->shared_data->simulation_active && !philosopher->survived)
        printf("%ld %d is eating\n",get_current_time(), philosopher->id);
    philosopher->last_meal_time = get_current_time();
    philosopher->meals_eaten++;
    usleep(philosopher->shared_data->time_to_eat * 1000);
    philosopher->last_meal_time = get_current_time();
}

void    leave_table(t_philosopher *philosopher)
{
    pthread_mutex_unlock(philosopher->right_fork);
    pthread_mutex_unlock(philosopher->left_fork);
    if (philosopher->shared_data->simulation_active && !philosopher->survived)
        printf("%ld %d ate %d times, and left table.\n",get_current_time() ,
                philosopher->id ,philosopher->shared_data->philosopher_must_eat);
    philosopher->survived = 1;
}

void    *thread_function(void *arg)
{
    t_philosopher        *philo;
    pthread_t       monitor_thread;
    
    philo = (t_philosopher *)arg;
    philo->last_meal_time = get_current_time();
    pthread_create(&monitor_thread, NULL, monitor_death, philo);
    pthread_detach(monitor_thread);
    while (philo->shared_data->simulation_active)
    {
        if (philo->id % 2 == 0)
            even_pick_fork(philo);
        else
            odd_pick_fork(philo);
        start_eating(philo);
        if (philo->meals_eaten == philo->shared_data->philosopher_must_eat)
        {
            leave_table(philo);
            return (NULL);
        }
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        if (philo->shared_data->simulation_active && !philo->survived)
            printf("%ld %d is sleeping\n",get_current_time() , philo->id);
        usleep(philo->shared_data->time_to_sleep * 1000);
        if (philo->shared_data->simulation_active && !philo->survived)
            printf("%ld %d is thinking\n",get_current_time(), philo->id);
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
        philosopher[i].survived = 0;
        philosopher[i].left_fork = &shared_data->forks[i];
        philosopher[i].right_fork = &shared_data->forks[(i + 1) % shared_data->number_of_philosophers];
        philosopher[i].shared_data = shared_data;
        i++;
    }
}


void thread_init(t_shared *shared)
{
    int i;
    t_philosopher philo[shared->number_of_philosophers];
    pthread_mutex_t forks[shared->number_of_philosophers];

    shared->philos = philo;
    shared->forks = forks;

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
    {
        usleep(100);
        pthread_mutex_destroy(&shared->forks[i]);
        i++;
    }
}

void    shared_data_init(t_shared *shared, char **argv)
{
    shared->simulation_active = 1;
    shared->number_of_philosophers = ft_atoi(argv[1]);
    shared->time_to_die = ft_atoi(argv[2]);
    shared->time_to_eat = ft_atoi(argv [3]);
    shared->time_to_sleep = ft_atoi(argv[4]);
    shared->philosopher_must_eat = ft_atoi(argv[5]);
}
int main(int argc, char **argv)
{
    t_shared        shared_data;

    check_args(argc, argv);
    shared_data_init(&shared_data, argv);
    thread_init(&shared_data);
    return (0);
}
