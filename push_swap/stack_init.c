#include "push_swap.h"

static long	ft_atol(const char *str)
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

void    stack_init(t_stack_node **a, t_stack_node **argv, bool flag_argc_2)
{
    long    nbr;
    int     i;

    i = 0;
    while(argv[i])
    {
        if (error_syntax(argv[i]))
            error_free(a, argv, flag_argc_2);
        nbr = ft_atol(argv[i]);
        if (nbr > INT_MAX || nbr < INT_MIN)
            error_free(a, argv, flag_argc_2);
        if (error_repetition(argv[i]))
            error_free(a, argv, flag_argc_2);
        append_node(a, (int)nbr);
        i++;
    }
    if (flag_argc_2)
        free_matrix(argv);
}