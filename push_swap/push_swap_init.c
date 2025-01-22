#include "push_swap.h"

void    set_current_position(t_stack_node *stack)
{
    int i;
    int centreline;

    i = 0;
    if (stack == NULL)
        return;
    centreline = stack_len(stack) / 2;
    while (stack)
    {
        stack->current_position = i;
        if (i <= centreline)
            stack->above_median = true;
        else
            stack->above_median = false;
        stack = stack->next;
        i++;
    }
    
}

static void set_target_node(t_stack_node *a, t_stack_node *b)
{
    long            best_match_index;
    t_stack_node    *current_a;
    t_stack_node    *target_node;

    while (b)
    {
        best_match_index = LONG_MAX;
        current_a = a;
        while (current_a)
        {
            if (current_a->value > b->value && current_a->value < best_match_index)
            {
                best_match_index = current_a->value;
                target_node = current_a;
            }
            current_a = current_a->next;
        }
        if (best_match_index == LONG_MAX)
            b->target_node = find_smallest(a);
        else
            b->target_node = target_node;
        b = b->next;
    }
    
}