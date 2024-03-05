/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:55:13 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 16:14:17 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static uint16_t remove_filename(const char *const str, uint16_t i, bool *const to_remove_array);
static char     *remove_chars(const char *const str, const bool *const to_remove_array);

char    *clear_redirs(const char *cmd_str)
{
    bool        *to_remove_array;
    uint16_t    i;
    char        master_quote;

    cmd_str = strdup_p(cmd_str);
    to_remove_array = (bool *)calloc_p(ft_strlen(cmd_str), sizeof(bool));
    master_quote = '\0';
    i = 0;
    while (cmd_str[i])
    {
        if (!master_quote && is_quote(cmd_str[i]))
            master_quote = cmd_str[i];
        else if (cmd_str[i] == master_quote)
            master_quote = '\0';
        if (!master_quote && is_redir(cmd_str[i]))
        {
            to_remove_array[i] = true;
            to_remove_array[i + 1] = is_redir(cmd_str[i + 1]);
            i = remove_filename(cmd_str, i, to_remove_array);
        }
        i++;
    }
    return (remove_chars(cmd_str, to_remove_array));
}

static uint16_t remove_filename(const char *const str, uint16_t i, bool *const to_remove_array)
{
    char    master_quote;

    i += 1 + is_redir(str[i + 1]);
    master_quote = '\0';
    while (str[i] && is_shell_space(str[i]))
        to_remove_array[i++] = true;
    while (str[i])
    {
        if (!master_quote && is_quote(str[i]))
            master_quote = str[i];
        else if (str[i] == master_quote)
            master_quote = '\0';
        if (!master_quote && is_shell_space(str[i]))
            break ;
        to_remove_array[i++] = true;
    }
    return (i - 1);
}

static char *remove_chars(const char *const str, const bool *const to_remove_array)
{
    uint16_t    to_remove_len;
    char        *new_str;
    uint16_t    i;
    uint16_t    j;

    i = 0;
    to_remove_len = 0;
    while (str[i])
        to_remove_len += to_remove_array[i++];
    new_str = (char *)malloc_p(sizeof(char) * (ft_strlen(str) - to_remove_len + 1));
    i = 0;
    j = 0;
    while (str[i])
    {
        if (!to_remove_array[i])
            new_str[j++] = str[i];
        i++;
    }
    new_str[j] = '\0';
    return (free_and_null((void **)&to_remove_array), free_and_null((void **)&str), new_str);
}