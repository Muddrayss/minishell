/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:58:27 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 13:54:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static void     fill_tree(t_list *params_head, t_tree **tree_head);
static t_cmd    *init_cmd(char *cmd_str);
static void     clear_redirs(char *cmd_str);
static void     remove_nums(char *cmd_str, uint8_t i);
static uint8_t  remove_filename(char *cmd_str, uint8_t i);
static t_list   *fill_redirs(char *cmd_str);
static void     fill_redir_input(t_list **redirs, char *str, uint8_t i);
static void     fill_redir_heredoc(t_list **redirs, char *str, uint8_t i);
static void     fill_redir_append(t_list **redirs, char *str, uint8_t i);
static void     fill_redir_output(t_list **redirs, char *str, uint8_t i);
static t_redir  *init_redir(void);

t_tree	*parser(t_list *params_head)
{
    t_tree   *tree_head;
    t_list   *tree_tmp;
    t_list   *params_tmp;
    t_lexer  *elem;

    merge_separators(params_head);
    // tree = malloc_p(sizeof(t_tree * ) * (ft_lstsize(params_head) + 1));
    fill_tree(params_head, &tree_head);
    return (tree_head);
}

static void     fill_tree(t_list *params_head, t_tree **tree_head)
{
    t_lexer  *elem;
    t_cmd    *elem_cmd;
    int8_t   flag;

    elem = (t_lexer *)params_head->content;
    if (elem->cmd_str || elem->token == SUBSHELL_END)
    {
        fill_tree(params_head->next, (*tree_head)->branches.branches_list);
        elem_cmd = init_cmd(elem->cmd_str);
        ft_treeadd_below((*tree_head)->branches.branches_list, ft_treenew(elem->token, elem_cmd));
        return ;
    }
    ft_treeadd_below(tree_head, ft_treenew(elem->token, NULL));
    fill_tree(params_head->next, (*tree_head)->branches.branches_list);
}

static t_cmd    *init_cmd(char *cmd_str)
{
    t_cmd   *cmd;

    if (!cmd_str)
        return (NULL);
    cmd = malloc_p(sizeof(t_cmd));
    cmd->redirs = fill_redirs(cmd_str);
    clear_redirs(cmd_str);
    cmd->cmd_str = cmd_str;
    return (cmd);
}
 //rimpiazza anche tab e \n con spazi (cosi' dopo si potra' fare split con spazi)
static void     clear_redirs(char *cmd_str)
{
    uint8_t i;

    i = 0;
    while (cmd_str[i])
    {
        if (cmd_str[i] == '<' || cmd_str[i] == '>')
        {
            cmd_str[i] = ' ';
            remove_nums(cmd_str, i);
            i = remove_filename(cmd_str, i);
        }
        if (is_shell_space(cmd_str[i])) //NON ELSE IF perche' remove filename incrementa la i uno di troppo
            cmd_str[i] = ' ';
        i++;
    }
}

static void     remove_nums(char *cmd_str, uint8_t i)
{
    uint8_t j;

    j = i;
    i += 1;
    j -= 1;
    if (cmd_str[i] == '&')
        i++;
    while (cmd_str[i] && ft_isdigit(cmd_str[i]))
        cmd_str[i++] = ' ';
    while (cmd_str[j] && ft_isdigit(cmd_str[j]))
        cmd_str[j--] = ' ';
}

static uint8_t  remove_filename(char *cmd_str, uint8_t i)
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
    uint8_t     i;

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

static void    fill_redir_input(t_list **redirs, char *str, uint8_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_INPUT_FD;
    node->fds[0] = get_num(str, i, AFTER);
    if (node->fds[0] == -42)
    {
        node->type = REDIR_INPUT;
        node->filename = get_filename(str, i);
    }
    ft_lstadd_back(redirs, ft_lstnew(node));
}

static void     fill_redir_heredoc(t_list **redirs, char *str, uint8_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_HEREDOC;
    node->filename = get_filename(str, i);
    ft_lstadd_back(redirs, ft_lstnew(node));
}

static void     fill_redir_append(t_list **redirs, char *str, uint8_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_APPEND_FD;
    node->fds[1] = get_num(str, i, AFTER);
    node->fds[0] = get_num(str, i, BEFORE);
    if (node->fds[1] == -42)
    {
        node->type = REDIR_APPEND;
        node->filename = get_filename(str, i);
    }
    if (node->fds[0] == -42)
        node->fds[0] = STDOUT_FILENO;
    ft_lstadd_back(redirs, ft_lstnew(node));
}

static void     fill_redir_output(t_list **redirs, char *str, uint8_t i)
{
    t_redir *node;

    node = init_redir();
    node->type = REDIR_OUTPUT_FD;
    node->fds[1] = get_num(str, i, AFTER);
    node->fds[0] = get_num(str, i, BEFORE);
    if (node->fds[1] == -42)
    {
        node->type = REDIR_OUTPUT;
        node->filename = get_filename(str, i);
    }
    if (node->fds[0] == -42)
        node->fds[0] = STDOUT_FILENO;
    ft_lstadd_back(redirs, ft_lstnew(node));
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
                    ft_lstdelone(head, node->next, del_content_lexer);
                }
                else
                    ft_strcat(elem->cmd_str, "&");
            }
            else if (elem->token == PIPE)
            {
                if (next_elem->token == PIPE)
                {
                    elem->token = OR;
                    ft_lstdelone(head, node->next, del_content_lexer);
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

static uint8_t  count_separators(t_list *node)
{
    uint8_t n_separators;
    t_lexer *elem;

    n_separators = 0;
    while (node)
    {
        elem = (t_lexer *)node->content;
        if (elem->token)
            n_separators++;
        node = node->next;
    }
    return (n_separators);
}
