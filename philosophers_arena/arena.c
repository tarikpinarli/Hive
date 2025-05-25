/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinarli <tpinarli@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:26:39 by tpinarli          #+#    #+#             */
/*   Updated: 2025/05/25 18:18:19 by tpinarli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_arena *arena_init(size_t size)
{
    t_arena *arena;

    arena = malloc(sizeof(t_arena));
    if (!arena)
        return NULL;
    arena->memory = malloc(size);
    if (!arena->memory)
    {
        free(arena);
        return NULL;
    }
    arena->size = size;
    arena->offset = 0;
    return (arena);
}

void *arena_alloc(t_arena *arena, size_t size)
{
    void *ptr;
    
    if (arena->offset + size > arena->size)
        return NULL;
    ptr = (char *)arena->memory + arena->offset;
    arena->offset += size;
    return (ptr);
}

void arena_destroy(t_arena *arena)
{
    if (!arena)
        return;
    free(arena->memory);
    free(arena);
}
