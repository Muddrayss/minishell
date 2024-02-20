/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:07:50 by egualand          #+#    #+#             */
/*   Updated: 2024/02/20 15:21:30 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int fail_after = 300;
static int num_allocs = 0;

void *cxmalloc(size_t size)
{
    //dprintf(2, "xmalloc(%zu) - num_allocs: %d\n", size, num_allocs);
    if (fail_after > 0 && num_allocs++ >= fail_after)
    {
        fputs("Out of memory\n", stderr);
        return (NULL);
    }
    
    #undef malloc
    
    return (malloc(size));
}