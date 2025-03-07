/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:17:26 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/07 16:59:11 by tpinarli         ###   ########.fr       */
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
            printf("%ld %d died\n",get_current_time() , data->id);
            exit(1);
        }
        usleep(100);
    }
    return NULL;
}

void    even_pick_fork(t_data *data)
{
    pthread_mutex_lock(data->right_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , data->id);
    pthread_mutex_lock(data->left_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , data->id);
}

void    odd_pick_fork(t_data *data)
{
    pthread_mutex_lock(data->left_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , data->id);
    pthread_mutex_lock(data->right_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , data->id);
}

void    start_eating(t_data *data)
{
    printf("%ld %d is eating\n",get_current_time(), data->id);
    data->last_meal_time = get_current_time();
    data->meals_eaten++;
    usleep(data->time_to_eat * 1000);
    data->last_meal_time = get_current_time();
}

void    leave_table(t_data *data)
{
    pthread_mutex_unlock(data->right_fork);
    pthread_mutex_unlock(data->left_fork);
    printf("%ld %d ate %d times, and left table.\n",get_current_time() ,
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
        pthread_mutex_unlock(data->right_fork);
        pthread_mutex_unlock(data->left_fork);

        printf("%ld %d is sleeping\n",get_current_time() , data->id);
        usleep(data->time_to_sleep * 1000);
        printf("%ld %d is thinking\n",get_current_time() , data->id);
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
void    thread_creation(pthread_t *threads, t_data *data, pthread_mutex_t *forks, char **argv)
{
    int i;
    int philo_num;

    i = 0;
    philo_num = ft_atoi(argv[1]);
    while (i < philo_num)
    {
        init_philosopher(&data[i], forks, i, argv);
        if (pthread_create(&threads[i], NULL, thread_function, &data[i]) != 0)
        {
            perror("pthread_create failed");//fix
            free(data);
            free(threads);
            exit(1);
        }
        i++;
    }
    i = 0;
    while (i < philo_num)
        pthread_join(threads[i++], NULL);
}
int main(int argc, char **argv)
{
    pthread_mutex_t *forks;
    pthread_t       *threads;
    t_data          *data;
    int             philo_num;
    int             i;

    check_args(argc, argv);
    philo_num = ft_atoi(argv[1]);
    data = (t_data *)malloc(philo_num * sizeof(t_data));
    threads = (pthread_t *)malloc(philo_num * sizeof(pthread_t));
    forks = (pthread_mutex_t *)malloc(philo_num * sizeof(pthread_mutex_t));
    if (!data || !threads || !forks)
        print_err_free_exit(data, threads, forks);
    thread_creation(threads, data, forks, argv);
    i = 0;
    while (i < philo_num)
        pthread_mutex_init(&forks[i++], NULL);
    
    free(data);
    free(threads);
    free(forks);
    return (0);
}
