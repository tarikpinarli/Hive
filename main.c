/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:19:54 by tpinarli          #+#    #+#             */
/*   Updated: 2024/10/31 11:06:00 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	main()
{
	const char	*ch;
	size_t	*result;
	ch = "ali";
	result = ft_strlen(ch);
	printf("%d", result);
	return (0);
}
