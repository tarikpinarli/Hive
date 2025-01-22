#include "push_swap.h"

t_stack_node *find_last_node(t_stack_node *stack)
{
    if (stack == NULL)
        return;
    while (stack->next)
        stack = stack->next;
    return (stack);
}

void    append_node(t_stack_node **stack, int nbr)
{
    t_stack_node    *node;
    t_stack_node    *last_node;

    if (stack == NULL)
        return;
    node = malloc(sizeof(t_stack_node));
    if (!node)
        return;
    node->next = NULL;
    node->value = nbr;
    if (*stack == NULL)
    {
        *stack = node;
        node->prev = NULL;
    }
    else
    {
        last_node = find_last_node(*stack);
        last_node->next = node;
        node->prev = last_node;
    }
    
}

t_stack_node    *find_smallest(t_stack_node *stack)
{
    int             smallest;
    t_stack_node    *smallest_node;

    smallest = INT_MAX;
    while (stack)
    {
        if (stack->value < smallest)
        {
            smallest = stack->value;
            smallest_node = stack;
        }
        stack = stack->next;
    }
    return (smallest_node);
}

t_stack_node    *return_cheapest(t_stack_node *stack)
{
    if (stack == NULL)
        return(NULL);
    while (stack)
    {
        if (stack->cheapest)
            return (stack);
        stack = stack->next;
    }
    return (NULL);
}