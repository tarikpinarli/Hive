#include "push_swap.h"

static void rotate(t_stack_node **stack)
{
    t_stack_node *head;
    t_stack_node *new_head;
    t_stack_node *last;

    if (!stack || !*stack || !(*stack)->next)
        return;
    head = *stack;
    new_head = head->next;
    last = find_last_node(stack);
    last->next = head;
    head->prev = last;
    new_head->prev = NULL;
    head->next = NULL;
    *stack = new_head;
}

void    ra(t_stack_node **a, bool checker)
{
    rotate(a);
    if (!checker)
        write(1, "ra\n", 3);
}

void    rb(t_stack_node **b, bool checker)
{
    rotate(b);
    if (!checker)
        write(1, "rb\n", 3);
}

void    rr(t_stack_node **a, t_stack_node **b, bool checker)
{
    rotate(a);
    rotate(b);
    if (!checker)
        write(1, "rr\n", 3);
}