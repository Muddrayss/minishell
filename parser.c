/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/30 14:55:04 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void		replace_placeholders(t_list *parsed_params);

t_list	*parser(t_list *lexered_params)
{
	t_data			*data;
	t_parser		*content_par;
	t_list			*parsed_params;
	t_list			*node;
	size_t			size;
	int8_t			to_skip;
	t_lexer			*prev_cmd_elem;
	t_lexer			*content_lex;
	static char		ph_semicolon = PH_SEMICOLON;
	static char		ph_redir_stop = PH_REDIR_STOP;

	data = get_data();
	int func_return ;
	if (!lexered_params)
		return (NULL);
	ft_lstdel_if(&lexered_params, &is_empty_cmd, &del_content_lexer);
	// TODO gestire caso tipo "> >" e "< <"
	node = lexered_params;
	parsed_params = NULL;
	prev_cmd_elem = NULL;
	func_return = 0;
	content_par = new_elem(&size, node);
	while (node)
	{
		to_skip = 1;
		content_lex = (t_lexer *)node->content;
		if (content_lex->type == CMD)
		{
			ft_strlcat(content_par->cmd_str, content_lex->str.cmd, size);
			prev_cmd_elem = content_lex;
			node = node->next;
		}
		else if (content_lex->type == TOKEN)
		{
			if (content_lex->str.token == PIPE)
			{
				ft_lstadd_back(&parsed_params, ft_lstnew(content_par));
				content_par = new_elem(&size, node->next);
				node = node->next;
				continue ;
			}				
			else if (content_lex->str.token == REDIR_L)
				to_skip += handle_redir_l(node, content_par);
			else if (content_lex->str.token == REDIR_R)
				to_skip += handle_redir_r(node, prev_cmd_elem, content_par);
			else if (content_lex->str.token == SEMICOLON)
			{
				ft_strlcat(content_par->cmd_str, &ph_semicolon, ft_strlen(content_par->cmd_str) + 2);
				ft_lstadd_back(&content_par->redirs, ft_lstnew(&ph_redir_stop));
			}
			// TODO valutare se fare qualche eccezione per i token di fila;
			// TODO se ci sono piu token di fila fare un controllo. ad esempio non puo esserci un | subito dopo un >
			if (func_return == -1)
				return (NULL);
			while (to_skip-- > 0)
				node = node->next;
		}
	}
	ft_lstadd_back(&parsed_params, ft_lstnew(content_par));
	ft_lstclear(&lexered_params, &del_content_lexer);
	data->lexered_params = NULL;
	replace_placeholders(parsed_params);
	return (parsed_params);
}

static void	replace_placeholders(t_list *parsed_params)
{
	t_list			*node;
	t_parser		*content_par;
	t_redir			*redir;
	unsigned int	i;

	node = parsed_params;
	while (node)
	{
		content_par = (t_parser *)node->content;
		i = 0;
		while (content_par->cmd_str[i] != '\0')
		{
			if (content_par->cmd_str[i] == PH_REDIR)
			{
				redir = (t_redir *)content_par->redirs->content;
				if (redir->type == REDIR_APPEND || redir->type == REDIR_OUTPUT)
					remove_num(&content_par->cmd_str, &i, LEFT);
				if (redir->type == REDIR_INPUT || redir->type == REDIR_APPEND
					|| redir->type == REDIR_OUTPUT || redir->type == REDIR_HEREDOC)
					remove_filename(&content_par->cmd_str, &i);
				else if (redir->type == REDIR_INPUT_FD
					|| redir->type == REDIR_OUTPUT_FD
					|| redir->type == REDIR_APPEND_FD)
					remove_num(&content_par->cmd_str, &i, RIGHT);
				content_par->cmd_str[i] = ' ';
			}
			i++;
		}
		node = node->next;
	}
}

