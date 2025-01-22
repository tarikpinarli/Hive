#include "push_swap.h"

bool    stack_sorted(t_stack_node *stack)
{
    if (stack == NULL)
        return (1);
    while (stack->next)
    {
        if (stack->value > stack->next->value)
            return (false);
        stack = stack->next;
    }
    return (true);
}

int stack_len(t_stack_node *stack)
{
    int count;

    count = 0;
    if (stack == NULL)
        return (count);
    while (stack)
    {
        count++;
        stack = stack->next;
    }
    return (count);
    
}

static t_stack_node *find_highest(t_stack_node *stack)
{
    int             highest;
    t_stack_node    *highest_node;

    if (stack == NULL)
        return(NULL);
    highest = INT_MIN;
    while (stack)
    {
        if (stack->value > highest)
        {
            highest = stack->value;
            highest_node = stack;
        }
        stack = stack->next;
    }
    return (highest_node);
}

void    tiny_sort(t_stack_node **a)
{
    t_stack_node    *highest_node;

    highest_node = find_highest(a);
    if (*a == highest_node)
        ra(a, false);
    else if ((*a)->next == highest_node)
        rra(a, false);
    if ((*a)->value > (*a)->next->value)
        sa(a, false);
}