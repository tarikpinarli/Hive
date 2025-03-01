/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:38:48 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/01 16:20:52 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *thread_function(void *thread_data)
{
    t_data  *data;

    data = (t_data *)thread_data;
    if (data->id % 2 == 0)
    {
        pthread_mutex_lock(data->right_fork);
        printf("Philosopher %d picked up right fork.\n", data->id);
        pthread_mutex_lock(data->left_fork);
        printf("Philosopher %d picked up left fork.\n", data->id);
    }
    else
    {
        pthread_mutex_lock(data->left_fork);
        printf("Philosopher %d picked up left fork.\n", data->id);
        pthread_mutex_lock(data->right_fork);
        printf("Philosopher %d picked up right fork.\n", data->id);
    }
    printf("Philosopher %d is eating...\n", data->id);
    usleep(data->time_to_eat);
    pthread_mutex_unlock(data->right_fork);
    pthread_mutex_unlock(data->left_fork);

    printf("Philosopher %d is now sleeping.\n", data->id);
    usleep(data->time_to_sleep);
    return NULL;   
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
    
    philo_num = atoi(argv[1]);
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
    {
        data[i].number_of_philosophers = philo_num;
        data[i].time_to_die = atoi(argv[2]);
        data[i].time_to_eat = atoi(argv [3]);
        data[i].time_to_sleep = atoi(argv[4]);
        data[i].philosopher_must_eat = atoi(argv[5]);
        data[i].meals_eaten = 0;
        data[i].left_fork = &forks[i];
        data[i].right_fork = &forks[(i + 1) % philo_num];
        data[i].id = i + 1;
        
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
    {
        pthread_join(threads[i], NULL);
        i++;
    }

    free(data);
    free(threads);
    free(forks);
    return (0);
}
