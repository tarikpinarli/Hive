/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 13:10:55 by tpinarli          #+#    #+#             */
/*   Updated: 2025/02/18 11:28:42 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	file_name(char *argv)
{
	int	arg_len;
	int	diff;

	if (!argv)
		return (0);
	arg_len = (int)ft_strlen(argv);
	if (arg_len < 4)
		return (0);
	diff = ft_strncmp((argv + arg_len - 4), ".ber", 4);
	if (diff == 0)
		return (1);
	else
		return (0);
}

void	arg_validation(int argc, char *argv)
{
	if (argc < 2 || argc > 2)
		print_error("invalid argument count.\n");
	if (!file_name(argv))
		print_error("invalid map name.\n");
}
