/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:30:47 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/25 14:21:59 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_wait_flag = 0;

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGUSR1)
		g_wait_flag = 1;
}

void	send_bit(int server_pid, char bit)
{
	if (bit)
	{
		if (kill(server_pid, SIGUSR1) == -1)
		{
			ft_printf("Kill in send_bit (SIGUSR1) failed\n");
			exit(1);
		}
	}
	else
	{
		if (kill(server_pid, SIGUSR2) == -1)
		{
			ft_printf("Kill in send_bit (SIGUSR2) failed\n");
			exit(1);
		}
	}
	while (!g_wait_flag)
		pause();
	g_wait_flag = 0;
}

void	send_message(int server_pid, char *msg)
{
	int	i;
	int	j;

	i = 0;
	while (msg[i])
	{
		j = 7;
		while (j >= 0)
		{
			send_bit(server_pid, (msg[i] >> j) & 1);
			j--;
		}
		i++;
	}
	j = 7;
	while (j >= 0)
	{
		send_bit(server_pid, ('\0' >> j) & 1);
		j--;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: ./server <server_pid> <message>\n");
		exit(1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
	{
		ft_printf("Invalid server_pid.\n");
		exit(1);
	}
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Client sigaction fail.\n");
		exit(1);
	}
	send_message(server_pid, argv[2]);
	return (0);
}
