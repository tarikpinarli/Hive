#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 10

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	*ft_calloc(size_t elementCount, size_t elementSize);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
void    *ft_memset(void *s, int c, size_t n);
size_t  ft_strlen(const char    *str);
void	ft_bzero(void *s, size_t n);
#endif