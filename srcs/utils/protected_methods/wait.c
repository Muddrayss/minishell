/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:38:07 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 17:26:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	wait_p(int32_t *const status)
{
	if (wait(status) == -1)
		ft_quit(ERR_WAIT, NULL);
}

void	waitpid_p(const pid_t pid, int32_t *const status, const int32_t options)
{
	if (waitpid(pid, status, options) == -1)
		ft_quit(ERR_WAIT, NULL);
}
