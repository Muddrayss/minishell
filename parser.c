/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/02/01 13:40:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void		replace_placeholders(t_list *parsed_params);
static char	get_token(t_list *node);
static void		add_soft_separator(t_parser *content_par, char placeholder);

t_list	*parser(t_list *lexered_params)
{
	t_data			*data;
	t_parser		*content_par;
	t_list			*parsed_params;
	t_list			*last_node;
	t_list			*node;
	int8_t			to_skip;
	t_lexer			*prev_cmd_elem;
	t_lexer			*content_lex;

	//TODO controllare la token streak qui incima in vece che in handle_redir

	data = get_data();
	if (!lexered_params)
		return (NULL);
	ft_lstdel_if(&lexered_params, &is_empty_cmd, &del_content_lexer);
	last_node = ft_lstlast(lexered_params);
	if (last_node && get_token(last_node))
		return(ft_parse_error(get_token(last_node)), NULL);
	// TODO gestire caso tipo "> >" e "< <"
	node = lexered_params;
	parsed_params = NULL;
	prev_cmd_elem = NULL;
	content_par = new_elem(node);
	while (node)
	{
		to_skip = 1;
		content_lex = (t_lexer *)node->content;
		if (content_lex->cmd)
		{
			ft_strcat(content_par->cmd_str, content_lex->cmd);
			prev_cmd_elem = content_lex;
			node = node->next;
		}
		else if (content_lex->token)
		{
			if (content_lex->token == PIPE)
			{
				if (node->next && get_token(node->next) == PIPE)
					add_soft_separator(content_par, PH_OR);
				else
				{
					ft_lstadd_back(&parsed_params, ft_lstnew(content_par));
					node = node->next;
					content_par = new_elem(node);
					continue ;
				}
				node = node->next;
			}				
			else if (content_lex->token == REDIR_L)
				to_skip += handle_redir_l(node, content_par);
			else if (content_lex->token == REDIR_R)
				to_skip += handle_redir_r(node, prev_cmd_elem, content_par);
			else if (content_lex->token == SEMICOLON)
				add_soft_separator(content_par, PH_SEMICOLON);
			else if (content_lex->token == AND)
				add_soft_separator(content_par, PH_AND);
			// TODO valutare se fare qualche eccezione per i token di fila;
			// TODO se ci sono piu token di fila fare un controllo. ad esempio non puo esserci un | subito dopo un >
			while (to_skip-- > 0)
				node = node->next;
		}
	}
	ft_lstadd_back(&parsed_params, ft_lstnew(content_par));
	ft_lstclear(&lexered_params, &del_content_lexer);
	data->lexered_params = NULL;
	return (replace_placeholders(parsed_params), parsed_params);
}

static void	add_soft_separator(t_parser *content_par, char placeholder)
{
	static char	ph_redir_stop = PH_REDIR_STOP;
	char		ph;

	ph = placeholder;
	ft_strlcat(content_par->cmd_str, &ph, ft_strlen(content_par->cmd_str) + 2);
	ft_lstadd_back(&content_par->redirs, ft_lstnew(&ph_redir_stop));
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

//potrebbe essere una macro
static char	get_token(t_list *node)
{
	return (((t_lexer *)node->content)->token);
}

