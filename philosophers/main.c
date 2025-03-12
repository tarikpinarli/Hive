/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:17:26 by tpinarli          #+#    #+#             */
/*   Updated: 2025/03/12 17:00:56 by tpinarli         ###   ########.fr       */
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
    int i;
    
    t_philosopher *philosopher = (t_philosopher *)arg;
    i = 0;
    while (!philosopher->survived)
    {
        if (get_current_time() - philosopher->last_meal_time > philosopher->shared_data->time_to_die)
        {
            printf("%ld %d died\n",get_current_time() , philosopher->id);
            philosopher->shared_data->simulation_active = 0;
            free_all(philosopher->shared_data, philosopher);
            exit(1);
        }
        usleep(1000);
    }
    return NULL;
}

void    even_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->right_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , philosopher->id);
    pthread_mutex_lock(philosopher->left_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , philosopher->id);
}

void    odd_pick_fork(t_philosopher *philosopher)
{
    pthread_mutex_lock(philosopher->left_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , philosopher->id);
    pthread_mutex_lock(philosopher->right_fork);
    printf("%ld %d has taken a fork\n"
            ,get_current_time() , philosopher->id);
}

void    start_eating(t_philosopher *philosopher)
{
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
    printf("%ld %d ate %d times, and left table.\n",get_current_time() ,
            philosopher->id ,philosopher->shared_data->philosopher_must_eat);
    philosopher->survived = 1;
}

void    *thread_function(void *philosopher_data)
{
    t_philosopher   *philosopher;
    pthread_t       monitor_thread;
    
    philosopher = (t_philosopher *)philosopher_data;
    philosopher->last_meal_time = get_current_time();
    pthread_create(&monitor_thread, NULL, monitor_death, philosopher);
    pthread_detach(monitor_thread);
    while (philosopher->shared_data->simulation_active)
    {
        if (philosopher->id % 2 == 0)
            even_pick_fork(philosopher);
        else
            odd_pick_fork(philosopher);
        start_eating(philosopher);
        if (philosopher->meals_eaten == philosopher->shared_data->philosopher_must_eat)
        {
            leave_table(philosopher);
            return (NULL);
        }
        pthread_mutex_unlock(philosopher->right_fork);
        pthread_mutex_unlock(philosopher->left_fork);

        printf("%ld %d is sleeping\n",get_current_time() , philosopher->id);
        usleep(philosopher->shared_data->time_to_sleep * 1000);
        printf("%ld %d is thinking\n",get_current_time() , philosopher->id);
        if (!philosopher->shared_data->simulation_active)
        {
            free_all(philosopher->shared_data, philosopher);
            exit(1);
        }
    }
    return NULL;
}

void    philosopher_data_init(t_shared *shared_data, t_philosopher *philosopher, int i)
{
    philosopher->id = i + 1;
    philosopher->meals_eaten = 0;
    philosopher->last_meal_time = 0;
    philosopher->survived = 0;
    philosopher->left_fork = &shared_data->forks[i];
    philosopher->right_fork = &shared_data->forks[(i + 1) % shared_data->number_of_philosophers];
    philosopher->shared_data = shared_data;
}

void    shared_data_init(t_shared *shared, char **argv)
{
    int i;
    
    shared->simulation_active = 1;
    shared->number_of_philosophers = ft_atoi(argv[1]);
    shared->time_to_die = ft_atoi(argv[2]);
    shared->time_to_eat = ft_atoi(argv [3]);
    shared->time_to_sleep = ft_atoi(argv[4]);
    shared->philosopher_must_eat = ft_atoi(argv[5]);
    shared->threads = (pthread_t *)malloc(shared->number_of_philosophers * sizeof(pthread_t));
    if (!shared->threads)
        print_err_exit("shared_data_init malloc failed.\n");
    shared->forks = (pthread_mutex_t *)malloc(shared->number_of_philosophers * sizeof(pthread_mutex_t));
    if (!shared->forks)
        print_err_exit("shared_data_init malloc failed.\n");
    i = 0;
    while (i < shared->number_of_philosophers)
        pthread_mutex_init(&shared->forks[i++], NULL);
}
void    thread_creation(t_shared *shared_data, t_philosopher *philosopher, char **argv)
{
    int i;
    int philo_num;

    i = 0;
    philo_num = ft_atoi(argv[1]);
    shared_data_init(shared_data, argv);
    while (i < philo_num)
    {
        philosopher_data_init(shared_data, &philosopher[i], i);
        if (pthread_create(&shared_data->threads[i], NULL, thread_function, &philosopher[i]) != 0)
        {
            perror("pthread_create failed");//fix
            //Free all
            exit(1);
        }
        i++;
    }
}
int main(int argc, char **argv)
{
    t_shared        *shared_data;
    t_philosopher   *philosophers;   
    int             philo_num;
    int             i;

    check_args(argc, argv);
    philo_num = ft_atoi(argv[1]);
    shared_data = (t_shared *)malloc(sizeof(t_shared));
    philosophers = (t_philosopher *)malloc(philo_num * sizeof(t_philosopher));
    if (!shared_data || !philosophers)
        print_err_free_exit(shared_data, philosophers);
    i = 0;
    thread_creation(shared_data, philosophers, argv);
    while (i < philo_num)
        pthread_join(shared_data->threads[i++], NULL);
    free_all(shared_data, philosophers);
    return (0);
}
