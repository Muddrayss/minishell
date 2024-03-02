/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:45:49 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 22:09:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static uint8_t  *get_errnos(void);

bool is_bad_errno(int errno_value)
{
    return (get_errnos()[errno_value]);
}

uint8_t *set_bad_errnos()
{
    static uint8_t  *errnos;
    static uint8_t  n_bad_errnos
    = sizeof(g_bad_errnos) / sizeof(g_bad_errnos[0]);
    uint8_t         i;

    i = -1;
    errnos = get_errnos();
    while (++i < n_bad_errnos)
        errnos[g_bad_errnos[i]] = true;
    return (errnos);
}

static uint8_t  *get_errnos(void)
{
    static uint8_t  errnos[N_ERRNOS];

    return (errnos); 
}