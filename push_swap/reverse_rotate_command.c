#include "push_swap.h"

static void reverse_rotate(t_stack_node **stack)
{
    t_stack_node    *head;
    t_stack_node    *last;

    if (stack == NULL || *stack == NULL || !(*stack)->next)
        return;
    last = find_last_node(stack);
    if (last == NULL)
        return;
    head = *stack;
    last->next->prev = NULL;
    last->prev = NULL;
    last->next = head;
    head->prev = last;
    *stack = last;
}

void    rra(t_stack_node **a, bool checker)
{
    reverse_rotate(a);
    if(!checker)
        write(1, "rra\n", 4);
}

void    rrb(t_stack_node **b, bool checker)
{
    reverse_rotate(b);
    if(!checker)
        write(1, "rrb\n", 4);
}

void    rrr(t_stack_node **a, t_stack_node **b, bool checker)
{
    reverse_rotate(a);
    reverse_rotate(b);
    if(!checker)
        write(1, "rrr\n", 4);
}
