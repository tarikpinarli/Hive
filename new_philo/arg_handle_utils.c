
#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return(1);
}

long	ft_atol(const char *str)
{
	long	num;
	int		isneg;
	int		i;

	num = 0;
	isneg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * isneg);
}

int	check_args(int argc, char **argv)
{
	int	i;

	if(argc != 5 && argc != 6)
	{
		printf("Invalid argument count.\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > INT_MAX)
		{
			printf("Arguments has to be in range of 0 and INT_MAX.\n");
			return (0);
		}
		i++;
	}
	i = 1;
	while(i < argc)
	{
		if (!ft_isdigit(argv[i]))
		{
			printf("Non digit input.\n");
			return (0);
		}
		i++;
	}
	return (1);
}
