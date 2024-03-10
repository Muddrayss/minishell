/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:14:34 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 15:42:17 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void		init_redir(t_list **const redirs, t_cc type,
					t_cc *const str, const int16_t heredoc_fileno);
static char		*get_filename(t_cc *const str);

char	parse_redirection(t_cc *const cmd_str, uint16_t *i, char *master_quote)
{
	char	type;

	type = -1;
	if (!*master_quote && is_quote(cmd_str[*i]))
		*master_quote = cmd_str[*i];
	else if (*master_quote == cmd_str[*i])
		*master_quote = '\0';
	if (!*master_quote && is_redir(cmd_str[*i]))
	{
		type = REDIR_INPUT * (cmd_str[*i] == '<')
			+ REDIR_OUTPUT * (cmd_str[*i] == '>');
		if (cmd_str[*i + 1] == cmd_str[*i])
		{
			type = REDIR_APPEND * (cmd_str[*i] == '>')
				+ REDIR_HEREDOC * (cmd_str[*i] == '<');
			(*i)++;
		}
	}
	return (type);
}

void	update_redirections_list(t_list **redirs, char type,
	t_cc *const cmd_str, int16_t *heredoc_fileno)
{
	if (type != -1)
	{
		init_redir(redirs, type, cmd_str, *heredoc_fileno);
	}
}

// Refactored fill_redirs function using the two new functions
t_list	*fill_redirs(t_cc *const cmd_str)
{
	t_list			*redirs;
	uint16_t		i;
	char			master_quote;
	static int16_t	heredoc_fileno;
	char			type;

	redirs = NULL;
	i = 0;
	master_quote = '\0';
	heredoc_fileno = 0;
	while (cmd_str[i])
	{
		type = parse_redirection(cmd_str, &i, &master_quote);
		update_redirections_list(&redirs, type, cmd_str + i, &heredoc_fileno);
		i++;
	}
	heredoc_fileno++;
	return (lstreverse(&redirs), redirs);
}

static void	init_redir(t_list **const redirs, t_cc type,
				t_cc *const str, const int16_t heredoc_fileno)
{
	t_redir	*redir;

	redir = (t_redir *)malloc_p(sizeof(t_redir), TMP);
	redir->type = type;
	redir->filename = get_filename(str);
	redir->heredoc_fileno = -1 * (type != REDIR_HEREDOC)
		+ heredoc_fileno * (type == REDIR_HEREDOC);
	lstadd_front(redirs, lstnew(redir, TMP));
}

static char	*get_filename(t_cc *const str)
{
	char		*filename;
	uint16_t	len;
	uint16_t	i;
	char		master_quote;

	i = 1;
	while (str[i] && is_shell_space(str[i]))
		i++;
	master_quote = '\0';
	len = 0;
	while (str[i + len])
	{
		if (!master_quote && is_quote(str[i + len]))
			master_quote = str[i + len];
		else if (master_quote == str[i + len])
			master_quote = '\0';
		if (!master_quote && is_shell_space(str[i + len]))
			break ;
		len++;
	}
	filename = malloc_p(sizeof(char) * len + 1, TMP);
	ft_strlcpy(filename, &str[i], len + 1);
	return (filename);
}
