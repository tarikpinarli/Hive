/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:54:32 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/28 15:09:18 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int		ft_printf(const char *first, ...);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_puthex_fd(void *ptr, int fd);
size_t	ft_strlen(const char	*str);
int		ft_putunsigned_fd(unsigned int n, int fd);
int		ft_putlowerhex(unsigned int nb, int fd);
int		ft_putupperhex(unsigned int nb, int fd);
#endif
