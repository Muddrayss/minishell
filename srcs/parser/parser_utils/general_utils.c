/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:24:52 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 10:29:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool    is_empty_cmd(const void *const content)
{
    const t_lexer *const    elem = (t_lexer *)content;

    if (elem->token == 0 && is_empty_str(elem->cmd_str))
        return (true);
    return (false);
}

bool    is_redir(const char c)
{
	return (c == '<' || c == '>');
}

void    del_content_parser(const void *const content)
{
    t_parser  *elem;

    if (!content)
        return ;
    elem = (t_parser *)content;
    if (elem->cmd)
    {
        free_and_null((void **)&elem->cmd->cmd_str);
        lstclear(&elem->cmd->redirs, &del_content_redirs);
        free_and_null((void **)&elem->cmd);
    }
    free_and_null((void **)&elem);
}

void    del_content_redirs(const void *const content)
{
    const t_redir *const    elem = (t_redir *)content;

    free_and_null((void **)&elem->filename);
    free_and_null((void **)&content);
}
