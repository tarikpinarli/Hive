/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:53:35 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/26 16:18:04 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_current_time_microseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

void	safe_sleep(t_philo *philo, long sleep_duration_ms)
{
	long	start_us;
	long	now_us;
	long	elapsed_us;

	start_us = get_current_time_microseconds();
	elapsed_us = 0;
	while (elapsed_us < sleep_duration_ms * 1000)
	{
		if (table_death_check(philo) || monitor_philo_death(philo))
			return ;
		usleep(1000);
		now_us = get_current_time_microseconds();
		elapsed_us = now_us - start_us;
	}
}
