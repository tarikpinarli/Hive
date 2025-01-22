#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft/libft.h"
# include <stdbool.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_stack_node t_stack_node;

struct s_stack_node
{
    int value;
    int current_position;   
    int final_index;
    int push_price;
    bool above_median;
    bool cheapest;
    t_stack_node *target_node;
    t_stack_node *next;
    t_stack_node *prev;
};

t_stack_node    *find_last_node(t_stack_node *stack);
t_stack_node    *find_smallest(t_stack_node *stack);
bool            stack_sorted(t_stack_node *stack);
static          t_stack_node *find_highest(t_stack_node *stack);
static void     rotate(t_stack_node **stack);
static void     reverse_rotate(t_stack_node **stack);
static void     push(t_stack_node **dest, t_stack_node **src);
static void     set_target_node(t_stack_node *a, t_stack_node *b);
static long	    ft_atol(const char *str);
int             stack_len(t_stack_node *stack);
void            set_current_position(t_stack_node *stack);
void            append_node(t_stack_node **stack, int nbr);
void            stack_init(t_stack_node **a, t_stack_node **argv, bool flag_argc_2);
void            pa(t_stack_node **a, t_stack_node **b, bool checker);
void            pb(t_stack_node **a, t_stack_node **b, bool checker);
void            ra(t_stack_node **a, bool checker);
void            rb(t_stack_node **b, bool checker);
void            rr(t_stack_node **a, t_stack_node **b, bool checker);
void            rra(t_stack_node **a, bool checker);
void            rrb(t_stack_node **b, bool checker);
void            rrr(t_stack_node **a, t_stack_node **b, bool checker);


#endif