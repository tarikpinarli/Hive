/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:17:26 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/05 16:38:36 by tpinarli         ###   ########.fr       */
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
    t_data *data = (t_data *)arg;
    while (!data->survived)
    {
        if (get_current_time() - data->last_meal_time > data->time_to_die)
        {
            printf("Philosopher %d has died.\n", data->id);
            exit(1);
        }
        usleep(1000);
    }
    return NULL;
}

void    even_pick_fork(t_data *data)
{
    pthread_mutex_lock(data->right_fork);
    pthread_mutex_lock(data->left_fork);
}

void    odd_pick_fork(t_data *data)
{
    pthread_mutex_lock(data->left_fork);
    pthread_mutex_lock(data->right_fork);
}

void    start_eating(t_data *data)
{
    printf("Philosopher %d is eating...\n", data->id);
    data->meals_eaten++;
    usleep(data->time_to_eat * 1000);
    data->last_meal_time = get_current_time();
}

void    leave_table(t_data *data)
{
    pthread_mutex_unlock(data->right_fork);
    pthread_mutex_unlock(data->left_fork);
    printf("Philosopher %d ate %d times, and left table.\n",
            data->id ,data->philosopher_must_eat);
    data->survived = 1;
}

void    *thread_function(void *thread_data)
{
    t_data      *data;
    pthread_t   monitor_thread;
    
    data = (t_data *)thread_data;
    data->last_meal_time = get_current_time();
    pthread_create(&monitor_thread, NULL, monitor_death, (void *)data);
    pthread_detach(monitor_thread);
    while (1)
    {
        if (data->id % 2 == 0)
            even_pick_fork(data);
        else
            odd_pick_fork(data);
        start_eating(data);
        if (data->meals_eaten == data->philosopher_must_eat)
        {
            leave_table(data);
            return (NULL);
        }
        usleep(data->time_to_eat);
        pthread_mutex_unlock(data->right_fork);
        pthread_mutex_unlock(data->left_fork);

        printf("Philosopher %d is now sleeping.\n", data->id);
        usleep(data->time_to_sleep * 1000);
        printf("Philosopher %d is now thinking.\n", data->id);
    }
    return NULL;
}

void    init_philosopher(t_data *data, pthread_mutex_t *forks, int i, char **argv)
{
    data->number_of_philosophers = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv [3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    data->philosopher_must_eat = ft_atoi(argv[5]);
    data->meals_eaten = 0;
    data->left_fork = &forks[i];
    data->right_fork = &forks[(i + 1) % data->number_of_philosophers];
    data->id = i + 1;
    data->survived = 0;
    data->last_meal_time = 0;
}
int main(int argc, char **argv)
{
    pthread_mutex_t *forks;
    pthread_t       *threads;
    t_data          *data;
    int             philo_num;
    int             i;

    if (argc != 6)
        return (1);
    
    philo_num = ft_atoi(argv[1]);
    data = (t_data *)malloc(philo_num * sizeof(t_data));
    threads = (pthread_t *)malloc(philo_num * sizeof(pthread_t));
    forks = (pthread_mutex_t *)malloc(philo_num * sizeof(pthread_mutex_t));
    if (!data || !threads || !forks)
    {
        printf("Memory allocation failed\n"); //free proper later
        return (1);
    }

    i = 0;
    while (i < philo_num)
        pthread_mutex_init(&forks[i++], NULL);
    i = 0;
    while (i < philo_num)
    {
        init_philosopher(&data[i], forks, i, argv);
        if (pthread_create(&threads[i], NULL, thread_function, (void *)&data[i]) != 0)
        {
            perror("pthread_create failed");
            free(data);
            free(threads);
            return (1);
        }
        i++;
    }
    i = 0;
    while (i < philo_num)
        pthread_join(threads[i++], NULL);
    free(data);
    free(threads);
    free(forks);
    return (0);
}
