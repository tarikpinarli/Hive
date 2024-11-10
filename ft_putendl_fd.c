/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 17:27:02 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/10 17:32:01 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	nl;

	nl = '\n';
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, &nl, 1);
}

/*int	main()
{
	char	s[] = "ates ediyorsun Tarik";

	ft_putendl_fd(s, 1);
	return (0);
}*/
