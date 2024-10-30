/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:32:07 by tpinarli          #+#    #+#             */
/*   Updated: 2024/10/30 16:56:10 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_isalpha(char ch)
{
	if (ch < 'A' || ch > 'z')
	{
		return (0);
	}
	if (ch < 'a' && ch > 'Z')
	{
		return (0);
	}
	return (1);
}

int main()
{
	char	ch;
	ch = 'Z';
	printf("%d",ft_isalpha(ch));
	return (0);
}
