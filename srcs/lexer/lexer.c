/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 14:35:10 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_list 	*lexer_add_cmd(t_list *lexered_params, uint16_t cmd_len, char *input);
static t_list 	*lexer_add_token(t_list *lexered_params, char c);

void    lexer(char *input)
{
    t_data          *data;
    char            *cmd_str;
    char            current_quote;
    uint16_t        cmd_len;

    data = get_data();
    current_quote = '\0';
    data->lexered_params = NULL;
    cmd_len = 0;
    while (true)
    {
        if (is_quote(*input))
        {
            if (!current_quote)
                current_quote = *input;
            else if (current_quote == *input)
                current_quote = '\0';
        }
        else if (!current_quote && (is_token(*input) || *input == '\0'))
        {
            cmd_str = (char *)malloc_p(sizeof(char) * (cmd_len + 1));
            ft_strlcpy(cmd_str, input - cmd_len, cmd_len + 1);
            data->lexered_params = lexer_add_cmd(data->lexered_params, cmd_len, cmd_str);
            data->lexered_params = lexer_add_token(data->lexered_params, *input);
            cmd_len = -1;
        }
        cmd_len++;
        if (!*input)
            break ;
        input++;
    }
    lstreverse(&data->lexered_params);
}

static t_list   *lexer_add_cmd(t_list *lexered_params, uint16_t cmd_len, char *cmd_str_raw)
{
    t_lexer   		*content;
    
    if (cmd_len <= 0)
        return (lexered_params);
    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = 0;
    content->cmd_str = cmd_str_raw;
    lstadd_front(&lexered_params, lstnew_p(content));
    return (lexered_params);
}

static t_list *lexer_add_token(t_list *lexered_params, char c)
{
    t_lexer   		*content;

    if (!c)
        return (lexered_params);
    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = c;
    content->cmd_str = NULL;
    lstadd_front(&lexered_params, lstnew_p(content));
    return (lexered_params);
}

