/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:24:52 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 18:12:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

bool    is_empty_cmd(const void *const content)
{
    t_lexer *elem;

    elem = (t_lexer *)content;
    if (elem->token == 0 && is_empty_str(elem->cmd_str))
        return (true);
    return (false);
}

void    del_content_parser(const void *const content)
{
    t_parser  *elem;

    if (!content)
        return ;
    elem = (t_parser *)content;
    lstclear(&elem->cmd->redirs, &del_content_redirs);
    free_and_null((void **)&elem->cmd->cmd_str);
    free_and_null((void **)&elem->cmd);
    free_and_null((void **)&elem);
}

void    del_content_redirs(const void *const content)
{
    t_redir *elem;

    elem = (t_redir *)content;
    free_and_null((void **)&elem->filename);
    free_and_null((void **)&content);
}
