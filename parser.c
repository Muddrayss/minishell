/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/11 15:17:57 by craimond         ###   ########.fr       */
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
	unsigned int	i;
	t_token			next_token;
	unsigned int	token_streak;

	content_par = new_elem(data);
	prev_cmd_elem = NULL;
	i = 0;
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
				i = 0;
				content_par = new_elem(&size, lexered_params->next, data);
				lexered_params = lexered_params->next;
				continue ;
			}
			else if (content_lex->str.token == REDIR_L)
				handle_redir_l(lexered_params, prev_cmd_elem, content_par, data);
			else if (content_lex->str.token == REDIR_R)
				handle_redir_r(lexered_params, prev_cmd_elem, content_par, data);
			else if (content_lex->str.token == ENV)
				handle_env(content_par, prev_cmd_elem, i++, data);
			//TODO valutare se fare qualche eccezione per i token di fila;
			token_streak = check_token_streak(&next_token, lexered_params);
			while (token_streak-- > 0)
				lexered_params = lexered_params->next;
		}
		lexered_params = lexered_params->next;
	}
	//fare sostituzione di tokens con placeholders e sostituzione di ENV variables con il loro valore
	return (parsed_params);
}

static void	handle_env(t_parser *content_par, t_lexer *prev_cmd_elem, unsigned int i, t_data *data)
{
	char			*path_name;
	unsigned int	i;

	path_name = ft_strdup(prev_cmd_elem);
	if (!path_name)
		ft_quit(15, "failed to allocate memory", data);
	i = 0;
	while (!is_shell_space(path_name[i]))
		i++;
	path_name[i] = '\0';
	content_par->env_vars[i] = getenv(path_name);
}
