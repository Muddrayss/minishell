/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:55:03 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 18:19:05 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void     fill_redir_input(t_list **redirs, char *str, uint32_t i);
static void     fill_redir_heredoc(t_list **redirs, char *str, uint32_t i, int32_t heredoc_fileno);
static void     fill_redir_output(t_list **redirs, char *str, uint32_t i, bool is_append);
static t_redir  *init_redir(void);
static char     *get_filename(char *str, uint32_t idx_redir);

t_list  *fill_redirs(char *cmd_str)
{
    t_list          *redirs;
    uint32_t        i;
    static int32_t  heredoc_fileno = 0;
    char            master_quote;

    i = 0;
    redirs = NULL;
    master_quote = '\0';
    while (cmd_str[i])
    {
        if (!master_quote && (is_quote(cmd_str[i])))
            master_quote = cmd_str[i];
        else if (master_quote && cmd_str[i] == master_quote)
            master_quote = '\0';
        if (!master_quote)
        {
            if (cmd_str[i] == '<')
            {
                if (cmd_str[i + 1] == '<')
                    fill_redir_heredoc(&redirs, cmd_str, ++i, heredoc_fileno);
                else
                    fill_redir_input(&redirs, cmd_str, i);
            }
            else if (cmd_str[i] == '>')
            {
                if (cmd_str[i + 1] == '>')
                    fill_redir_output(&redirs, cmd_str, ++i, true);
                else
                    fill_redir_output(&redirs, cmd_str, i, false);
            }
        }
        i++;
    }
    return (heredoc_fileno++, lstreverse(&redirs), redirs);
}
//TODO mergiare tutte le fill_Redirs
static void fill_redir_heredoc(t_list **redirs, char *str, uint32_t i, int32_t heredoc_fileno)
{
    t_redir *redir;

    redir = init_redir();
    redir->type = REDIR_HEREDOC;
    redir->filename = get_filename(str, i);
    redir->heredoc_fileno = heredoc_fileno;
    lstadd_front(redirs, lstnew_p(redir));
}

static void    fill_redir_input(t_list **redirs, char *str, uint32_t i)
{
    t_redir         *redir;

    redir = init_redir();
    redir->type = REDIR_INPUT;
    redir->filename = get_filename(str, i);
    lstadd_front(redirs, lstnew_p(redir));
}

static void     fill_redir_output(t_list **redirs, char *str, uint32_t i, bool is_append)
{
    t_redir *redir;

    redir = init_redir();
    redir->type = REDIR_APPEND * (is_append) + REDIR_OUTPUT * (!is_append);
    redir->filename = get_filename(str, i);
    lstadd_front(redirs, lstnew_p(redir));
}

static t_redir *init_redir(void)
{
    t_redir *redir;

    redir = (t_redir *)malloc_p(sizeof(t_redir));
    redir->filename = NULL;
    redir->heredoc_fileno = -1;
    redir->type = -1;
    return (redir);
}

static char *get_filename(char *str, uint32_t idx_redir)
{
	char 		*filename;
	uint32_t 	len;
	uint32_t 	i;
	
	filename = NULL;
	i = idx_redir + 1;
	while (str[i] != '\0' && is_shell_space(str[i]))
		i++;
	len = 0;
	while (str[i + len] && !is_shell_space(str[i + len]) && !is_quote(str[i + len]))
		len++;
	filename = calloc_p(len + 1, sizeof(char));
	ft_strlcpy(filename, &str[i], len + 1);
	return (filename);
}


