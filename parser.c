/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/01/25 19:25:44 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void		replace_placeholders(t_list *parsed_params, t_data *data);
static int8_t 	handle_env(t_list *lexered_params, t_data *data);
static void		handle_slash(t_list *node, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data);

t_list	*parser(t_list *lexered_params, t_data *data)
{
	t_parser		*content_par;
	t_list			*parsed_params;
	t_list			*node;
	size_t			size;
	t_lexer			*prev_cmd_elem;
	t_lexer			*content_lex;
	unsigned int	token_streak;

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
			func_return = handle_env(node, data);
		if (func_return == -1)
			return (NULL);
		node = node->next;
	}
	node = lexered_params;
	content_par = new_elem(&size, node, data);
	while (node)
	{
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
				content_par = new_elem(&size, node->next, data);
				node = node->next;
				continue ;
			}
			else if (content_lex->str.token == REDIR_L)
				handle_redir_l(node, content_par, data);
			else if (content_lex->str.token == REDIR_R)
				handle_redir_r(node, prev_cmd_elem, content_par, data);
			else if (content_lex->str.token == SLASH)
				handle_slash(node, prev_cmd_elem, content_par, data);
			// TODO valutare se fare qualche eccezione per i token di fila;
			// TODO se ci sono piu token di fila fare un controllo. ad esempio non puo esserci un | subito dopo un >
			if (func_return == -1)
				return (NULL);
			token_streak = check_token_streak(NULL, node);
			while (token_streak-- > 0)
				node = node->next;
		}
	}
	ft_lstadd_back(&parsed_params, ft_lstnew(content_par));
	ft_lstclear(&lexered_params, &del_content_lexer);
	data->lexered_params = NULL;
	// TODO replace placeholders e' come se non funzionasse
	replace_placeholders(parsed_params, data);
	return (parsed_params);
}

static void	replace_placeholders(t_list *parsed_params, t_data *data)
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
					remove_num(&content_par->cmd_str, &i, LEFT, data);
				if (redir->type == REDIR_INPUT || redir->type == REDIR_APPEND
					|| redir->type == REDIR_OUTPUT || redir->type == REDIR_HEREDOC)
					remove_filename(&content_par->cmd_str, &i, data);
				else if (redir->type == REDIR_INPUT_FD
					|| redir->type == REDIR_OUTPUT_FD
					|| redir->type == REDIR_APPEND_FD)
					remove_num(&content_par->cmd_str, &i, RIGHT, data);
				content_par->cmd_str[i] = ' ';
			}
			else if (content_par->cmd_str[i] == PH_INVALID_ENV)
				content_par->cmd_str[i] = ' ';
			i++;
		}
		node = node->next;
	}
}

static int8_t	handle_env(t_list *lexered_params, t_data *data)
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
		ft_quit(15, "failed to allocate memory", data);
	j = 0;
	while (var_name[j] && !is_shell_space(var_name[j]))
		j++;
	var_name[j] = '\0';
	env_var = getenv(var_name);
	replace_env_var(&next_cmd_elem->str.cmd, env_var, data);
	return (free(var_name), 0);
}

static void	handle_slash(t_list *node, t_lexer *prev_cmd_elem, t_parser *content_par, t_data *data)
{
	int			size;
	int			len;
	char		*tmp;
	t_lexer		*next_cmd_elem;
	static char	placehodler = PH_ABS_PATH;

	next_cmd_elem = get_next_cmd_elem(node);
	if (next_cmd_elem != (t_lexer *)node->next)
		ft_parse_error('/');
	tmp = ft_strdup(next_cmd_elem->str.cmd);
	if (!tmp)
		ft_quit(98, "failed to allocate memory", data);
	while (next_cmd_elem->str.cmd[size] && !is_shell_space(next_cmd_elem->str.cmd[size]))
		size++;
	tmp[size - 1] = '\0';
	size += 3; //2 per eventuali . o .. e \0
	content_par->bin_path = ft_calloc(size, sizeof(char));
	if (!content_par->bin_path)
		ft_quit(99, "failed to allocate memory", data);
	len = ft_strlen(prev_cmd_elem->str.cmd);
	if (prev_cmd_elem->str.cmd[len - 1] == '.')
	{
		ft_strlcat(content_par->bin_path, ".", size);
		if (prev_cmd_elem->str.cmd[len - 1] == '.')
			ft_strlcat(content_par->bin_path, ".", size);
	}
	else
		ft_strlcat(content_par->bin_path, &placehodler, size);
	ft_strlcat(content_par->bin_path, "/", size);
	ft_strlcat(content_par->bin_path, tmp, size);
	free(tmp);
}
