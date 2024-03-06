/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:14:34 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 21:32:04 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void		init_redir(t_list **const redirs, const char type, const char *const str, const int16_t heredoc_fileno);
static char		*get_filename(const char *const str);

t_list	*fill_redirs(const char *const cmd_str)
{
	t_list			*redirs;
	uint16_t		i;
	char			master_quote;
	char			type;
	static int16_t	heredoc_fileno = 0;

	i = 0;
	redirs = NULL;
	master_quote = '\0';
	while (cmd_str[i])
	{
		type = -1;
		if (!master_quote && is_quote(cmd_str[i]))
			master_quote = cmd_str[i];
		else if (master_quote == cmd_str[i])
			master_quote = '\0';
		if (!master_quote && is_redir(cmd_str[i]))
		{
			type = REDIR_INPUT * (cmd_str[i] == '<') + REDIR_OUTPUT * (cmd_str[i] == '>');
			if (cmd_str[i + 1] == cmd_str[i])
			{
				type = REDIR_APPEND * (cmd_str[i] == '>') + REDIR_HEREDOC * (cmd_str[i] == '<');
				i++;
			}
			init_redir(&redirs, type, cmd_str + i, heredoc_fileno);
		}
		i++;
	}
	return (heredoc_fileno++, lstreverse(&redirs), redirs);
}

static void	init_redir(t_list **const redirs, const char type, const char *const str, const int16_t heredoc_fileno)
{
	t_redir	*redir;

	redir = (t_redir *)malloc_p(sizeof(t_redir), TMP);
	redir->type = type;
	redir->filename = get_filename(str);
	redir->heredoc_fileno = -1 * (type != REDIR_HEREDOC) + heredoc_fileno * (type == REDIR_HEREDOC);
	lstadd_front(redirs, lstnew(redir, TMP));
}

static char	*get_filename(const char *const str)
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
