/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:45:49 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 15:03:09 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static bool  *get_errnos(void);

bool is_bad_errno(const int errno_value)
{
    return (get_errnos()[errno_value]);
}

void    set_errnos(void)
{
    bool                    *errnos;
    uint8_t                 i;
    static const uint8_t    n_bad_errnos
    = sizeof(g_bad_errnos) / sizeof(g_bad_errnos[0]);

    i = 0;
    errnos = get_errnos();
    while (i < n_bad_errnos)
        errnos[g_bad_errnos[i++]] = true;
}

static bool  *get_errnos(void)
{
    static bool errnos[N_ERRNOS] = {false};

    return (errnos); 
}