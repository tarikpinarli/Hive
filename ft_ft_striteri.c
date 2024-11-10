/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_striteri.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:23:37 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/10 17:01:22 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (!s)
		return;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

void sample_func(unsigned int i, char *c)
{
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 32; // Convert lowercase to uppercase
}

int main(void)
{
    char str[] = "hello world";

    ft_striteri(str, sample_func);
    printf("Modified string: %s\n", str);

    return 0;
}
