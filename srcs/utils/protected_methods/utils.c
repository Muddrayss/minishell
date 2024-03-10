/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:45:49 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:13:24 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	set_errnos(void)
{
	bool					*errnos;
	uint8_t					i;
	static const uint8_t	n_bad_errnos
		= sizeof(g_bad_errnos) / sizeof(g_bad_errnos[0]);

	i = 0;
	errnos = get_errnos();
	while (i < n_bad_errnos)
		errnos[g_bad_errnos[i++]] = true;
}

bool	*get_errnos(void)
{
	static bool	errnos[N_ERRNOS] = {false};

	return (errnos);
}
