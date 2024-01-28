/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/28 16:41:34 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void		replace_placeholders(t_list *parsed_params);
static int8_t 	handle_env(t_list *lexered_params);

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
	while (node)
	{
		content_lex = (t_lexer *)node->content;
		if (content_lex->type == TOKEN && content_lex->str.token == ENV)
			func_return = handle_env(node);
		if (func_return == -1)
			return (NULL);
		node = node->next;
	}
	node = lexered_params;
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
	// TODO replace placeholders e' come se non funzionasse
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
			else if (content_par->cmd_str[i] == PH_INVALID_ENV)
				content_par->cmd_str[i] = ' ';
			i++;
		}
		node = node->next;
	}
}

static int8_t	handle_env(t_list *lexered_params)
{
	char				*var_name;
	char 				*env_var;
	unsigned int 		j;
	t_lexer				*next_cmd_elem;
	t_token				next_token;

	// placeholder per il $
	next_cmd_elem = get_next_cmd_elem(lexered_params);
	check_token_streak(&next_token, lexered_params);
	if (next_token == ENV)
		return (ft_parse_error('$'));
	var_name = ft_strdup(next_cmd_elem->str.cmd);
	if (!var_name)
		ft_quit(15, "failed to allocate memory");
	j = 0;
	while (var_name[j] && !is_shell_space(var_name[j]))
		j++;
	var_name[j] = '\0';
	env_var = getenv(var_name);
	replace_env_var(&next_cmd_elem->str.cmd, env_var);
	return (free(var_name), 0);
}
