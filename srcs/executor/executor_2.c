/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:27:52 by egualand          #+#    #+#             */
/*   Updated: 2024/03/10 15:29:35 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_tree	*skip_till_semicolon(const t_tree *const node)
{
	t_parser	*elem;

	if (!node)
		return (NULL);
	elem = (t_parser *)node->content;
	if (elem->type == SEMICOLON)
		return (node->right);
	return (skip_till_semicolon(node->right));
}

void	child(const t_tree *const node,
	const int16_t fds[5], const int8_t prev_type)
{
	const t_parser *const	elem = (t_parser *)node->content;

	if (prev_type == PIPELINE)
		dup2_p(fds[2], STDIN_FILENO);
	replace_env_vars(&elem->cmd->cmd_str, false);
	replace_wildcards(&elem->cmd->cmd_str);
	exec_redirs(elem->cmd->redirs);
	exec(ft_getenv("PATH="), elem->cmd->cmd_str);
}

void	parent(const t_tree *const node, int16_t fds[5], const pid_t pid)
{
	const t_parser *const	elem = (t_parser *)node->content;
	int32_t					status;

	reset_fd(&fds[1]);
	fds[2] = fds[0];
	if (elem->type != PIPELINE)
	{
		waitpid_p(pid, &status, 0);
		g_status = WEXITSTATUS(status);
		reset_fd(&fds[0]);
	}
}

void	wait_for_children(const t_tree *const node)
{
	int32_t		status;
	uint16_t	n_to_wait;

	n_to_wait = get_n_pipelines(node);
	while (n_to_wait--)
	{
		waitpid_p(0, &status, 0);
		g_status = WEXITSTATUS(status);
	}
}

uint16_t	get_n_pipelines(const t_tree *const node)
{
	t_parser	*elem;
	t_parser	*left_elem;
	uint16_t	n;

	n = 0;
	if (!node)
		return (n);
	elem = (t_parser *)node->content;
	if (elem->type == PIPELINE)
	{
		left_elem = (t_parser *)node->left->content;
		if (left_elem->type == CMD && !is_builtin(left_elem->cmd->cmd_str))
			n++;
	}
	n += get_n_pipelines(node->right);
	return (n);
}
