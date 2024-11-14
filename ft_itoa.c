/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:01:59 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/14 12:30:06 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		digit_count(int nb);
static char		*append(char *str, int nb, int len);
static char		*incase(int n);

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	long int		nb;
	int				len;

	nb = n;
	i = 0;
	if (n == -2147483648 || n == 0)
		return (incase(n));
	if (n < 0)
	{
		i = 1;
		nb = -n;
	}
	len = digit_count(nb) + i;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	str = append(str, nb, len);
	str[len] = '\0';
	return (str);
}

static char	*incase(int n)
{
	char	*big;
	char	*small;

	if (n == -2147483648)
	{
		big = (char *)malloc(15);
		ft_strlcpy(big, "-2147483648", 12);
		return (big);
	}
	if (n == 0)
	{
		small = (char *)malloc(2);
		small = "0";
		return (small);
	}
	return (NULL);
}

static char	*append(char *str, int nb, int len)
{
	while (nb != 0)
	{
		str[len - 1] = 48 + (nb % 10);
		nb = nb / 10;
		len--;
	}
	return (str);
}

static int	digit_count(int nb)
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
