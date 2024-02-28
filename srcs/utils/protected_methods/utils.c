/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:45:49 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 13:59:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static uint8_t  *get_bad_errnos(void);

bool is_bad_errno(int errno_value)
{
    return (get_bad_errnos()[errno_value]);
}

uint8_t *set_bad_errnos()
{
    static uint8_t  *bad_errnos;
    static uint8_t  n_bad_errnos
        = sizeof(g_bad_errnos) / sizeof(g_bad_errnos[0]);

    bad_errnos = get_bad_errnos();
    while (n_bad_errnos--)
        bad_errnos[n_bad_errnos] = g_bad_errnos[n_bad_errnos];
    return (bad_errnos);
}

static uint8_t  *get_bad_errnos(void)
{
    static uint8_t  bad_errnos[N_ERRNOS];

    return (bad_errnos); 
}