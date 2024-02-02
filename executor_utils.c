/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:59:44 by craimond          #+#    #+#             */
/*   Updated: 2024/01/31 03:50:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static char *get_env_name(char *str);

void    replace_env_vars(char **str)
{
    char				*env_name;
    int                 env_name_len;
    char				*env_value;
    unsigned int		i;

    i = 0;
    while ((*str)[i] != '\0')
    {
        if ((*str)[i] == '$')
        {
            env_name = get_env_name(*str + i + 1); //fino a spazio, '\0' o '$'
            if (env_name)
            {
                if (ft_strncmp(env_name, "?", 2) != 0)
                    env_value = ft_getenv(env_name);
                else
                    env_value = ft_itoa(g_status);
                env_name_len = ft_strlen(env_name);
                *str = ft_insert_str(*str, env_value, i, i + env_name_len + 1);
                if (!*str)
                    ft_quit(14, "failed to allocate memory");
                free(env_name);
                i += env_name_len;
            }
        }
        i++;
    }
}

static char *get_env_name(char *str)
{
    char	*env_name;
    int		i;

    i = 0;
    if (!str || str[i] == '\0' || str[i] == '$' || is_shell_space(str[i]))
        return (NULL);
    while (str[i] != '\0' && !is_shell_space(str[i]) && str[i] != '$')
        i++;
    env_name = (char *)ft_calloc(i + 1, sizeof(char));
    if (!env_name)
        ft_quit(15, "failed to allocate memory");
    ft_strlcpy(env_name, str, i + 1);
    return (env_name);
}

bool check_last_subcmd(char *cmd_str)
{
    static unsigned int i = 0;

    while (cmd_str[i])
    {
        if (cmd_str[i] == PH_SEMICOLON || cmd_str[i] == PH_OR || cmd_str[i] == PH_AND)
            return (i++, false);
        i++;
    }
    return (i++, true);
}
