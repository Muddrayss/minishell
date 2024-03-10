/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 15:31:20 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	launch_commands(const t_tree *const node,
				const int8_t prev_type, int16_t fds[5]);
static void	launch_builtin_cmd(const t_tree *const node,
				const int8_t prev_type, int16_t fds[5]);
static void	launch_standard_cmd(const t_tree *const node,
				const int8_t prev_type, int16_t fds[5]);

static void	init_fds(int16_t fds[5])
{
	fds[0] = -42;
	fds[1] = -42;
	fds[2] = -42;
	fds[3] = -42;
	fds[4] = -42;
}

void	executor(const t_tree *const parsed_params)
{
	const uint8_t	original_status = g_status;
	uint8_t			heredoc_status;
	int16_t			fds[5];

	init_fds(fds);
	fds[3] = dup_p(STDIN_FILENO);
	fds[4] = dup_p(STDOUT_FILENO);
	heredoc_status = 0;
	create_heredocs(parsed_params, &heredoc_status);
	dup2_p(fds[3], STDIN_FILENO);
	if (heredoc_status != 0)
	{
		if (heredoc_status == 130)
			g_status = 130;
		return ;
	}
	g_status = (uint8_t)original_status;
	set_signals(S_COMMAND, true);
	launch_commands(parsed_params, -1, fds);
	wait_for_children(parsed_params);
	dup2_p(fds[3], STDIN_FILENO);
}

static void	launch_commands(const t_tree *const node,
	const int8_t prev_type, int16_t fds[5])
{
	t_parser	*elem;
	t_parser	*left_elem;

	if (!node)
		return ;
	elem = (t_parser *)node->content;
	if (elem->type != CMD)
	{
		left_elem = (t_parser *)node->left->content;
		if (elem->type == PIPELINE)
			pipe_p(fds);
		if (left_elem->cmd && is_builtin(left_elem->cmd->cmd_str))
			launch_builtin_cmd(node, prev_type, fds);
		else
			launch_standard_cmd(node, prev_type, fds);
		if ((elem->type == AND && g_status != 0)
			|| (elem->type == OR && g_status == 0))
			launch_commands(skip_till_semicolon(node), -1, fds);
		else
			launch_commands(node->right, elem->type, fds);
		return ;
	}
	child(node, fds, prev_type);
}

static void	launch_builtin_cmd(const t_tree *const node,
	const int8_t prev_type, int16_t fds[5])
{
	const t_parser *const	elem = (t_parser *)node->content;

	if (elem->type == PIPELINE)
	{
		dup2_p(fds[1], STDOUT_FILENO);
		reset_fd(&fds[1]);
	}
	fds[2] = fds[0];
	set_signals(S_COMMAND, true);
	launch_commands(node->left, prev_type, fds);
	dup2_p(fds[4], STDOUT_FILENO);
}

static void	launch_standard_cmd(const t_tree *const node,
	const int8_t prev_type, int16_t fds[5])
{
	const t_parser *const	elem = (t_parser *)node->content;
	const pid_t				pid = fork_p();

	if (pid == 0)
	{
		if (elem->type == PIPELINE)
		{
			dup2_p(fds[1], STDOUT_FILENO);
			reset_fd(&fds[0]);
			reset_fd(&fds[1]);
		}
		set_signals(S_COMMAND, true);
		launch_commands(node->left, prev_type, fds);
		wait_for_children(node->left);
		release_resources();
		exit(g_status);
	}
	else
		parent(node, fds, pid);
}
