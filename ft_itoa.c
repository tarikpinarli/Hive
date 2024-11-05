/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:01:59 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/05 14:15:03 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		digit_count(int nb);
char	*append(char *str, int nb, int len);

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		nb;
	int		len;
	int		last_index;

	nb = n;
	i = 0;
	if (n < 0)
	{
		i = 1;
		nb = -n;
	}
	len = digit_count(nb) + i;
	last_index = len;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str = append(str, nb, len);
	str[last_index] = '\0';
	return (str);
}

char	*append(char *str, int nb, int len)
{
	while (nb != 0)
	{
		str[len - 1] = 48 + (nb % 10);
		nb = nb / 10;
		len--;
	}
	return (str);
}

int	digit_count(int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

/*int	main(void)
{
	int		n;
	char	*s;

	n = -245465565;
	s = ft_itoa(n);
	printf("%s", s);
	return (0);
}*/
