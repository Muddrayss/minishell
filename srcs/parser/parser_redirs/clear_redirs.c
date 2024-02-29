/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:55:13 by craimond          #+#    #+#             */
/*   Updated: 2024/02/29 17:40:59 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char     *remove_chars(char *str, bool *to_remove_array);
static uint32_t remove_filename(char *str, uint32_t i, bool *to_remove_array);

char    *clear_redirs(char *cmd_str)
{
    uint32_t    i;
    bool        *to_remove_array;
    char        master_quote;

    cmd_str = ft_strdup(cmd_str);
    if (!cmd_str)
        ft_quit(ERR_MEM, "minishell: failed to allocate memory");
    to_remove_array = (bool *)calloc_p(ft_strlen(cmd_str), sizeof(bool));
    master_quote = '\0';
    i = -1;
    while (cmd_str[++i])
    {
        if (!master_quote && (cmd_str[i] == '\'' || cmd_str[i] == '"'))
            master_quote = cmd_str[i];
        else if (master_quote && cmd_str[i] == master_quote)
            master_quote = '\0';
        if (!master_quote)
        {
            if (cmd_str[i] == '<' || cmd_str[i] == '>')
            {
                to_remove_array[i] = true;
                to_remove_array[i + 1] = (cmd_str[i + 1] == '<' || cmd_str[i + 1] == '>');
                i = remove_filename(cmd_str, i, to_remove_array);
            }
        }
    }
    return (remove_chars(cmd_str, to_remove_array));
}

static uint32_t remove_filename(char *str, uint32_t i, bool *to_remove_array)
{
    i += 1 + (str[i + 1] == '<' || str[i + 1] == '>');
    while (str[i] && is_shell_space(str[i]))
        to_remove_array[i++] = true;
    while (str[i] && !is_shell_space(str[i])) // && !is_quote(str[i]))
        to_remove_array[i++] = true;
    return (i - 1);
}

static char *remove_chars(char *str, bool *to_remove_array)
{
    uint32_t    to_remove_len;
    char        *new_str;
    uint32_t    i;
    uint32_t    j;

    i = -1;
    to_remove_len = 0;
    while (str[++i])
        to_remove_len += to_remove_array[i];
    new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(str) - to_remove_len + 1));
    i = -1;
    j = 0;
    while (str[++i])
        if (!to_remove_array[i])
            new_str[j++] = str[i];
    new_str[j] = '\0';
    return (free(to_remove_array), free(str), new_str);
}