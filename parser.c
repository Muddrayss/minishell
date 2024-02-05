/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 13:37:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     *fill_tree(t_list *params, t_tree *tree_head, int is_first);
static t_list   *skip_parenthesis(t_list *params);
static t_cmd    *init_cmd(char *cmd_str);
static void     clear_redirs(t_list *redirs, char *cmd_str);
static void     remove_fd_num(char *cmd_str, uint32_t idx_redir, int8_t before_after);
static uint32_t remove_filename(char *cmd_str, uint32_t i);
static t_list   *fill_redirs(char *cmd_str);
static void     fill_redir_input(t_list **redirs, char *str, uint32_t i);
static void     fill_redir_heredoc(t_list **redirs, char *str, uint32_t i);
static void     fill_redir_append(t_list **redirs, char *str, uint32_t i);
static void     fill_redir_output(t_list **redirs, char *str, uint32_t i);
static t_redir  *init_redir(void);
static bool     is_separator(char token);
static void     merge_separators(t_list **head);
static uint32_t get_fd_num(char *str, uint32_t idx_redir, uint8_t before_after);

t_tree	*parser(t_list *params_head)
{
    t_tree   *tree_head;

    merge_separators(&params_head);
    // tree = malloc_p(sizeof(t_tree * ) * (ft_lstsize(params_head) + 1));
	tree_head = treenew_p(0, NULL);
    fill_tree(params_head, tree_head, true);
    return (tree_head);
}

static void     *fill_tree(t_list *params, t_tree *tree_head, int is_first)
{
	t_lexer	*elem;
	t_list	*first_occ;

	elem = (t_lexer *)params->content;
	first_occ = NULL;
	if (elem->token)
	{
		if (elem->token ==  SUBSHELL_END)
			return (tree_head);
		else if (elem->token == SUBSHELL_START)
		{
			first_occ = params;
			params = skip_parenthesis(params);
		}
		treeadd_below(&tree_head, treenew_p(elem->token, NULL));
		if (first_occ)
			fill_tree(first_occ, tree_head->left, true); //fills the subshell
		else
			fill_tree(params->prev, tree_head->left, false);
		treeadd_below(&tree_head->right, fill_tree(params->next, tree_head->right, true));
		return (tree_head);
	}
	if (is_first == false)
		return (treenew_p(CMD, init_cmd(elem->cmd_str)));
	fill_tree(params->next, tree_head, false);
    return (tree_head);
}

static t_list	*skip_parenthesis(t_list *params)
{
	uint32_t	n_open;
	t_lexer		*elem;

	n_open = 0;
	while (n_open)
	{
		elem = (t_lexer *)params->content;
		if (elem->token == SUBSHELL_START)
			n_open++;
		else if (elem->token == SUBSHELL_END)
			n_open--;
		params = params->next;
	}
	return (params);
}

// Defined but N-E-V-E-R used
static t_cmd    *init_cmd(char *cmd_str)
{
    t_cmd   *cmd;

    if (!cmd_str)
        return (NULL);
    cmd = malloc_p(sizeof(t_cmd));
    cmd->redirs = fill_redirs(cmd_str);
    clear_redirs(cmd->redirs, cmd_str);
    cmd->cmd_str = cmd_str;
    return (cmd);
}

 //rimpiazza anche tab e \n con spazi (cosi' dopo si potra' fare split con spazi)
static void     clear_redirs(t_list *redirs, char *cmd_str)
{
    int32_t i;
    t_redir *redir;

    i = 0;
    while (cmd_str[i])
    {
        if (cmd_str[i] == '<' || cmd_str[i] == '>')
        {
            redir = (t_redir *)redirs->content;
            cmd_str[i] = ' ';
            if (redir->fds[1] != -42)
                remove_fd_num(cmd_str, i, AFTER);
            if (redir->fds[0] != -42)
                remove_fd_num(cmd_str, i, BEFORE);
            i = remove_filename(cmd_str, i);
        }
        if (is_shell_space(cmd_str[i])) //NON ELSE IF perche' remove filename incrementa la i uno di troppo
            cmd_str[i] = ' ';
        i++;
    }
}

static void     remove_fd_num(char *cmd_str, uint32_t idx_redir, int8_t before_after)
{
    uint32_t i;

    i = idx_redir + (before_after == AFTER) - (before_after == BEFORE);
    if (before_after == AFTER)
    {
        if (cmd_str[i] == '&')
            cmd_str[i++] = ' ';
        while (cmd_str[i] && ft_isdigit(cmd_str[i]))
            cmd_str[i++] = ' ';
    }
    else
    {
        while (cmd_str[i] && ft_isdigit(cmd_str[i]))
            cmd_str[i--] = ' ';
    }
}

static uint32_t  remove_filename(char *cmd_str, uint32_t i)
{
    while (cmd_str[i] && is_shell_space(cmd_str[i]))
        cmd_str[i++] = ' ';
    while (cmd_str[i] && !is_shell_space(cmd_str[i]))
        cmd_str[i++] = ' ';
    return (i);
}

static t_list  *fill_redirs(char *cmd_str)
{
    t_list      *redirs;
    uint32_t     i;

    i = 0;
    while (cmd_str[i])
    {
        redirs = malloc_p(sizeof(t_list));
        if (cmd_str[i] == '<')
        {
            if (cmd_str[i + 1] == '<')
                fill_redir_heredoc(&redirs, cmd_str, i++);
            else
                fill_redir_input(&redirs, cmd_str, i);
        }
        if (cmd_str[i] == '>')
        {
            if (cmd_str[i + 1] == '>')
                fill_redir_append(&redirs, cmd_str, i++);
            else
                fill_redir_output(&redirs, cmd_str, i);
        }
        i++;
    }
    return (redirs);
}

static uint32_t get_fd_num(char *str, uint32_t idx_redir, uint8_t before_after)
{
    uint32_t    i;
    int32_t     num;

    num = -42;
    i = idx_redir + (before_after == AFTER) - (before_after == BEFORE);
    if (before_after == AFTER)
    {
        if (str[i] == '&' && ft_isdigit(str[i + 1]))
            num = ft_atou(&str[i + 1]);
    }
    else
    {
        while (str[i] && ft_isdigit(str[i]))
            i--;
        if (is_shell_space(str[i]))
            num = ft_atou(&str[i + 1]);
    }
    return (num);
}

static char	*get_filename(char *str, uint32_t idx_redir)
{
	char 		*filename;
	uint32_t 	len;
	uint32_t 	i;
	
	filename = NULL;
	i = idx_redir + 1;
	while (str[i] && is_shell_space(str[i]))
		i++;
	len = 0;
	while (str[i + len] && !is_shell_space(str[i + len]))
		len++;
	filename = calloc_p(len + 1, sizeof(char));
	ft_strlcpy(filename, &str[i], len + 1);
	return (filename);
}

static void    fill_redir_input(t_list **redirs, char *str, uint32_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_INPUT_FD;
    node->fds[0] = get_fd_num(str, i, AFTER);
    if (node->fds[0] == -42)
    {
        node->type = REDIR_INPUT;
        node->filename = get_filename(str, i);
    }
    lstadd_back(redirs, lstnew_p(node));
}

static void     fill_redir_heredoc(t_list **redirs, char *str, uint32_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_HEREDOC;
    node->filename = get_filename(str, i);
    lstadd_back(redirs, lstnew_p(node));
}
//TODO da mergiare con fill_redir_output
static void     fill_redir_append(t_list **redirs, char *str, uint32_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_APPEND_FD;
    node->fds[1] = get_fd_num(str, i, AFTER);
    node->fds[0] = get_fd_num(str, i, BEFORE);
    if (node->fds[1] == -42)
    {
        node->type = REDIR_APPEND;
        node->filename = get_filename(str, i);
    }
    if (node->fds[0] == -42)
        node->fds[0] = STDOUT_FILENO;
    lstadd_back(redirs, lstnew_p(node));
}

static void     fill_redir_output(t_list **redirs, char *str, uint32_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_OUTPUT_FD;
    node->fds[1] = get_fd_num(str, i, AFTER);
    node->fds[0] = get_fd_num(str, i, BEFORE);
    if (node->fds[1] == -42)
    {
        node->type = REDIR_OUTPUT;
        node->filename = get_filename(str, i);
    }
    if (node->fds[0] == -42)
        node->fds[0] = STDOUT_FILENO;
    lstadd_back(redirs, lstnew_p(node));
}

static t_redir *init_redir(void)
{
    t_redir *redir;

    redir = malloc_p(sizeof(t_redir));
    redir->fds[0] = -42;
    redir->fds[1] = -42;
    redir->filename = NULL;
    return (redir);
}

static bool is_separator(char token)
{
    return (token == SEMICOLON || token == PIPE || token == AMPERSAND || token == PARENTHESIS_L || token == PARENTHESIS_R);
}

static void merge_separators(t_list **head)
{
    t_list  *node;
    t_lexer *elem;
    t_lexer *next_elem;
    t_lexer *prev_elem;

    node = *head;
    while (node)
    {
        elem = (t_lexer *)node->content;
        next_elem = (t_lexer *)node->next->content;
        prev_elem = (t_lexer *)node->prev->content;
        if (elem->token && is_separator(elem->token))
        {
            if (elem->token == AMPERSAND)
            {
                if (next_elem->token == AMPERSAND)
                {
                    elem->token = AND;
                    lstremoveone(node->next, del_content_lexer);
                }
                else
                    ft_strcat(prev_elem->cmd_str, "&");
            }
            else if (elem->token == PIPE)
            {
                if (next_elem->token == PIPE)
                {
                    elem->token = OR;
                    lstremoveone(node->next, del_content_lexer);
                }
                else
                    elem->token = PIPELINE;
            }
            else if (elem->token == PARENTHESIS_L)
                elem->token = SUBSHELL_START;
            else if (elem->token == PARENTHESIS_R)
                elem->token = SUBSHELL_END;
        }
        node = node->next;
    }
}
