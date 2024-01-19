/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:08 by craimond          #+#    #+#             */
/*   Updated: 2024/01/19 18:12:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    executor(t_list *parsed_params, t_data *data)
{
    t_parser    *content;
    t_list      *node;
    int         fds[2];
    int         prev_output_fd;
    pid_t       pid;

	while (node)
	{
		content = (t_parser *)node->content;
		if (pipe(fds) == -1)
            ft_quit(18, NULL, data);
        pid = fork();
        if (pid == -1)
            ft_quit(19, NULL, data);
        if (pid == 0)
        {
            handle_command(content, data);
        }
        else
        {
            if (close(fds[0]) == -1)
                ft_quit(20, NULL, data);
        }
		node = node->next;
	}    
}

static void handle_command(t_parser *content, t_data *data)
{
    exec_redirs(content->redirs, data);

}

static void exec_redirs(t_list *redirs, t_data *data)
{
    t_list  *node;
    t_redir *redir;

    node = redirs;
    while (node)
    {
        redir = (t_redir *)redirs->content;
        if (redir->fds[0] != -42)
            dup2(redir->fds[0], STDIN_FILENO);
        node = node->next;
    }
}
