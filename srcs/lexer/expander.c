/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:18:56 by craimond          #+#    #+#             */
/*   Updated: 2024/02/26 12:36:44 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char    *expand(char *str)
{
    uint32_t        i;
    char            *text_block;
    uint32_t        start;
    char            *tmp;
    char            master_quote;

    i = -1;
    start = 0;    
    while (true)
    {
        if (str[i] == '\'' || str[i] == '"' || !str[i])
        {
            text_block = (char *)malloc_p(sizeof(char) * (i - start));
            ft_strlcpy(text_block, str, i - start);
            if (master_quote != '\'')
                text_block = replace_env_vars(text_block);
            if (!master_quote)
                text_block = replace_wildcards(text_block);
            tmp = str;
            str = (char *)malloc_p(sizeof(char) * (start + ft_strlen(text_block) + ft_strlen(str + i) + 1));
            ft_strlcpy(str, tmp, start + 1);
            ft_strcat(str, text_block);
            ft_strcat(str, tmp + 1);
            free(tmp);
            free(text_block);
            if (!master_quote)
                master_quote = str[i];
            else if (master_quote == str[i])
                master_quote = '\0';
            start = i;
        }
        if (!str[i++])
            break ;
    }
    return (str);
}
