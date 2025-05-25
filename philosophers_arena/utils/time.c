/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:53:35 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 19:54:01 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_current_time_microseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}