/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/10 14:44:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*parser(t_list *lexered_params, t_data *data)
{
	t_list			*parsed_params;
	t_parser		*content_par;
	t_lexer			*prev_cmd_elem;
	t_lexer			*content_lex;
	char			*cmd_str;
	size_t			size;
	t_redir_type	redir_type;

	content_par = new_elem(data);
	size = get_len(lexered_params) + 1;
	prev_cmd_elem = NULL;
	content_par->cmd_str = (char *)ft_calloc(size, sizeof(char));
	if (!cmd_str)
		ft_quit(11, "failed to allocate memory", data);
	while (lexered_params)
	{
		content_lex = (t_lexer *)lexered_params->content;
		if (content_lex->type == CMD)
		{
			ft_strlcat(content_par->cmd_str, content_lex->str.cmd, size);
			prev_cmd_elem = content_lex;
		}
		else if (content_lex->type == TOKEN)
		{
			if (content_lex->str.token == PIPE)
			{
				ft_lstadd_back(parsed_params, ft_lstnew(content_par));
				content_par = new_elem(data);
			}
			else if (content_lex->str.token == REDIR_L)
				handle_redir_l(lexered_params, prev_cmd_elem, content_par, data);
			else if (content_lex->str.token == REDIR_R)
				handle_redir_r(lexered_params, prev_cmd_elem, content_par, data);
			else if (content_lex->str.token == ENV)
				handle_env();
			if (content_lex->str.token == REDIR_L || content_lex->str.token == REDIR_R)
			{
				redir_type = ((t_redir *)(((t_list *)(content_par->redirections))->content))->type;
				if (redir_type == REDIR_HEREDOC || redir_type == REDIR_APPEND || redir_type == REDIR_APPEND_FD)
					lexered_params = lexered_params->next;
			}
		}
		lexered_params = lexered_params->next;
	}
	return (parsed_params);
}
