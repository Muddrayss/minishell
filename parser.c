/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/09 19:55:32 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*new_elem(t_data *data);
static void		remove_near_redirs(char *str, unsigned int *cmd_len);

t_list	*parser(t_list *lexered_params, t_data *data)
{
	t_list			*parsed_params;
	t_parser		*content_par;
	t_lexer			content_lex_prev;
	t_lexer			*content_lex;
	char			*cmd_str;
	size_t			size;

	content_par = new_elem(data);
	size = get_len(lexered_params);
	cmd_str = (char *)ft_calloc(size, sizeof(char));
	if (!cmd_str)
		ft_quit(11, "failed to allocate memory", data);
	while (lexered_params)
	{
		content_lex = (t_lexer *)lexered_params->content;
		if (content_lex->type == CMD)
		{
			ft_strlcat(cmd_str, content_lex->str.cmd, size);
			content_lex_prev = *content_lex;
		}
		else if (content_lex->type == TOKEN)
		{
			if (content_lex->str.token == PIPE)
			{
				ft_lstadd_back(parsed_params, ft_lstnew(content_par));
				content_par = new_elem(data);
			}
			else if (content_lex->str.token == REDIR_L)
				handle_redir_l(content_lex_prev.str.cmd, content_lex, &content_par, data);
		}
		lexered_params = lexered_params->next;
	}
	return (parsed_params);
}

static void	handle_redir_l(char *prev_cmd_str, t_parser *content_par, t_data *data)
{
	t_redir	*redir_content;

	redir_content = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_content)
		ft_quit(12, "failed to allocate memory", data);
	init_redir(redir_content);
	while (ft_isdigit(*prev_cmd_str))
		prev_cmd_str--;
	if (is_shell_space(*prev_cmd_str))
		redir_content->fds[0] = ft_atoi(prev_cmd_str);
	//fare il controllo anche sul next
	content_par->redirections = NULL;
	ft_lstadd_front(&content_par->redirections, ft_lstnew(redir_content));
}

static unsigned int	get_len(t_list *lexered_params)
{
	unsigned int	cmd_len;
	t_lexer			l_content;

	cmd_len = 0;
	l_content = *((t_lexer *)lexered_params->content);
	while (lexered_params)
	{
		l_content = *((t_lexer *)lexered_params->content);
		if (l_content.type == CMD)
			cmd_len += ft_strlen(l_content.str.cmd);
		lexered_params = lexered_params->next;
	}
}

static t_parser	*new_elem(t_data *data)
{
	t_parser *elem;

	elem = (t_parser *)malloc(sizeof(t_parser));
	if (!elem)
		ft_quit(10, "failed to allocate memory", data);
	elem->cmd_args = NULL;
	elem->redirections = NULL;
}