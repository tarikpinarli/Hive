/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:38:58 by tpinarli          #+#    #+#             */
/*   Updated: 2024/11/01 21:12:22 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTLIB_H
#define FTLIB_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int	ft_atoi(const char *str);
int strncmp(const char *s1, const char *s2, size_t n);
int ft_isalnum(int ch);
int ft_isdigit(int ch);
int ft_isalpha(int ch);
int ft_isprint(int  ch);
int	ft_isascii(int	ch);
size_t	ft_strlen(const char	*str);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif

