/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:54:46 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/01 19:09:37 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*int	main()
{
	char	s[] = "ali ata bak";
	size_t	i = 2;
	ft_bzero(s+4,i);
	printf("%s", s);
	return (0);
}*/
