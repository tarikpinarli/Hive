
# include "push_swap.h"

int main(int argc, char **argv)
{
    t_stack_node *a;
    t_stack_node *b;

    a = NULL;
    b = NULL;
    if (argc == 1 || (argc == 2 && !argv[1][0]))
        return (1);
    else if (argc == 2)
        argv = ft_split(argv[1], ' ');
    stack_init(&a, argv + 1, argc == 2);
    if (!stack_sorted(a))
    {
        if (stack_len(a) == 2)
            sa(&a, false);
        if (stack_len(a) == 3)
            tiny_sort(&a);
        else
            push_swap(&a, &b);
    }
    free_stack(&a);
}