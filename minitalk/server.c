/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:30:59 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/25 12:21:46 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_iterative_power(int nb, int power)
{
	int	val;

	val = 1;
	if (power < 0)
		return (0);
	while (power != 0)
	{
		val = val * nb;
		power--;
	}
	return (val);
}

char	binary_to_ascii(const char *buffer)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < 8)
	{
		if (buffer[i] == '1')
			sum += ft_iterative_power(2, 7 - i);
		i++;
	}
	return ((char)sum);
}

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static int	buffer_index = 0;
	static int	message_index = 0;
	static char	buffer[8];
	static char	message[2097153];

	(void)context;
	if (signum == SIGUSR1)
		buffer[buffer_index++] = '1';
	else
		buffer[buffer_index++] = '0';
	if (buffer_index == 8)
	{
		message[message_index++] = binary_to_ascii(buffer);
		buffer_index = 0;
	}
	if (message[message_index - 1] == '\0')
	{
		ft_printf("%s", message);
		message_index = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		ft_printf("Kill in server handle_signal failed.\n");
		exit(1);
	}
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Server sigaction failed.\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Server sigaction failed.\n");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
