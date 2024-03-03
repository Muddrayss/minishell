/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:07:50 by egualand          #+#    #+#             */
/*   Updated: 2024/03/03 19:02:24 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static int fail_after = 300;
static int num_allocs = 0;

void *cxmalloc(const size_t size)
{
    //dprintf(2, "xmalloc(%zu) - num_allocs: %d\n", size, num_allocs);
    if (fail_after > 0 && num_allocs++ >= fail_after)
    {
        fputs("Out of memory\n", stderr);
        return (NULL);
    }
    
    #undef malloc //TODO to remove, against norme
    
    return (malloc(size));
}