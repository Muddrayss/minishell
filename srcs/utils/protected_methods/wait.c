/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:38:07 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 21:11:20 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	wait_p(int32_t *const status)
{
	if (wait(status) == -1)
		panic(ERR_WAIT, NULL);
}

void	waitpid_p(const pid_t pid, int32_t *const status, const int32_t options)
{
	if (waitpid(pid, status, options) == -1)
		panic(ERR_WAIT, NULL);
}
