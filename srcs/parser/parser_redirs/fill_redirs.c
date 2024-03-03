/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:55:03 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 20:13:40 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void     init_redir(t_list **const redirs, const char type, const char *const str, const int16_t heredoc_fileno);
static char     *get_filename(const char *const str);

t_list  *fill_redirs(const char *const cmd_str)
{
    t_list          *redirs;
    uint16_t        i;
    char            master_quote;
    char            type;
    static int16_t  heredoc_fileno = 0;

    i = 0;
    redirs = NULL;
    master_quote = '\0';
    while (cmd_str[i])
    {
        if (!master_quote && (is_quote(cmd_str[i])))
            master_quote = cmd_str[i];
        else if (master_quote && cmd_str[i] == master_quote)
            master_quote = '\0';
        if (!master_quote && is_redir(cmd_str[i]))
        {
            if (cmd_str[i] == '<')
                type = REDIR_HEREDOC * (cmd_str[i + 1] == '<') + REDIR_INPUT * (cmd_str[i + 1] != '<');
            else if (cmd_str[i] == '>')
                type = REDIR_APPEND * (cmd_str[i + 1] == '>') + REDIR_OUTPUT * (cmd_str[i + 1] != '>');
            init_redir(&redirs, type, cmd_str + i, heredoc_fileno);
        }
        i += 1 + (type == REDIR_HEREDOC || type == REDIR_APPEND);
    }
    return (heredoc_fileno++, lstreverse(&redirs), redirs);
}

//TODO leak with echo text > filename (filename not freed)
static void init_redir(t_list **const redirs, const char type, const char *const str, const int16_t heredoc_fileno)
{
    t_redir *redir;

    redir = (t_redir *)malloc_p(sizeof(t_redir));
    redir->type = type;
    redir->filename = get_filename(str + (type == REDIR_HEREDOC || type == REDIR_APPEND));
    redir->heredoc_fileno = -1 * (type != REDIR_HEREDOC) + heredoc_fileno * (type == REDIR_HEREDOC);
    lstadd_front(redirs, lstnew_p(redir));
}

static char *get_filename(const char *const str) //str in posizione della redir (> <)
{
	char 		*filename;
	uint16_t 	len;
	uint16_t 	i;
	
	filename = NULL;
    i = 1;
	while (str[i] != '\0' && is_shell_space(str[i]))
		i++;
	len = 0;
	while (str[i + len] && !is_shell_space(str[i + len]) && !is_quote(str[i + len]))
		len++;
	filename = calloc_p(len + 1, sizeof(char));
	ft_strlcpy(filename, &str[i], len + 1);
	return (filename);
}


