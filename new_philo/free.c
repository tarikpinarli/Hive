
#include "philo.h"

void    free_all(t_shared *shared_data)
{
    int i;

    //if (&shared_data->print_mutex)
    pthread_mutex_destroy(&shared_data->print_mutex);
    //if (&shared_data->shared_state_mutex)
    pthread_mutex_destroy(&shared_data->shared_state_lock);
    i = 0;
    if (shared_data->forks)
    {
        while (i < shared_data->num_philo)
            pthread_mutex_destroy(&shared_data->forks[i++]);
        free(shared_data->forks);
    }
    if (shared_data->philo)
		free(shared_data->philo);
}