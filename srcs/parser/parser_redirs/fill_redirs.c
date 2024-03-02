/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:55:03 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 19:56:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void     init_redir(t_list **redirs, char type, char *str, uint16_t heredoc_fileno);
static char     *get_filename(char *str);

t_list  *fill_redirs(char *cmd_str)
{
    t_list          *redirs;
    uint16_t        i;
    static uint16_t heredoc_fileno = 0;
    char            master_quote;
    char            type;

    i = -1;
    redirs = NULL;
    master_quote = '\0';
    while (cmd_str[++i])
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
    }
    return (heredoc_fileno++, lstreverse(&redirs), redirs);
}

static void init_redir(t_list **redirs, char type, char *str, uint16_t heredoc_fileno)
{
    t_redir *redir;

    redir = (t_redir *)malloc_p(sizeof(t_redir));
    redir->type = type;
    redir->filename = get_filename(str);
    redir->heredoc_fileno = -1 * (type != REDIR_HEREDOC) + heredoc_fileno * (type == REDIR_HEREDOC);
    lstadd_front(redirs, lstnew_p(redir));
}

static char *get_filename(char *str) //str in posizione della redir (> <)
{
	char 		*filename;
	uint32_t 	len;
	uint32_t 	i;
	
	filename = NULL;
    i = 1; //per skippare > < 
	while (str[i] != '\0' && is_shell_space(str[i]))
		i++;
	len = 0;
	while (str[i + len] && !is_shell_space(str[i + len]) && !is_quote(str[i + len]))
		len++;
	filename = calloc_p(len + 1, sizeof(char));
	ft_strlcpy(filename, &str[i], len + 1);
	return (filename);
}


