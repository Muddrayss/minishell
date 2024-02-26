/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/02/26 12:45:46 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool 	is_token(char c);
static void 	lexer_add_cmd(t_list **lexered_params, uint32_t cmd_len, char *input);
static void 	lexer_add_token(t_list **lexered_params, char c);
static void     restore_placeholders(char *str);

t_list	*lexer(char *input)
{
    uint32_t        cmd_len;
    char            *cmd_str;
    char            current_quote;
    t_list         	**lexered_params;

	lexered_params = (t_list **)malloc_p(sizeof(t_list *));
    *lexered_params = NULL;
    current_quote = '\0';
    get_data()->lexered_params = lexered_params;
    cmd_len = 0;
    cmd_str = ft_strdup(input);
    if (!cmd_str)
        ft_quit(ERR_MEM, "Error: failed to allocate memory");
    while (*input != '\0')
    {
        if (*input == '\'' || *input == '"')
        {
            if (!current_quote)
                current_quote = *input;
            else if (current_quote == *input)
                current_quote = '\0';
        }
        else if (!current_quote && (is_token(*input) || !*input))
        {
            cmd_str[cmd_len] = '\0';
            if (cmd_len > 0)
                lexer_add_cmd(lexered_params, cmd_len, cmd_str);
            lexer_add_token(lexered_params, *input++);
            free(cmd_str);
            cmd_str = ft_strdup(input);
            cmd_len = 0;
        }
        else
            cmd_len++;
        input += *input != '\0';
    }
    lstreverse(lexered_params);
    return (*lexered_params);
}

static void lexer_add_cmd(t_list **lexered_params, uint32_t cmd_len, char *cmd_str_raw)
{
    int32_t         i;
    t_lexer   		*content;
    char            master_quote;
    
    cmd_str_raw = expand(cmd_str_raw);
    master_quote = '\0';
    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = 0;
    content->cmd_str = (char *)malloc_p(sizeof(char) * (cmd_len + 1));
    i = 0;
    while (*cmd_str_raw)
    {
        if (*cmd_str_raw == '\'' || *cmd_str_raw == '"')
        {
            if (!master_quote)
                master_quote = *cmd_str_raw;
            else if (master_quote == *cmd_str_raw)
                master_quote = '\0';
            content->cmd_str[i++] = *cmd_str_raw;
        }
        if (*cmd_str_raw != master_quote) //non ELSE IF perch' le quotes devono essere scritte
        {
            if (*cmd_str_raw == '<')
                content->cmd_str[i++] = g_ph_redirl;
            else if (*cmd_str_raw == '>')
                content->cmd_str[i++] = g_ph_redirr;
            else
                content->cmd_str[i++] = *cmd_str_raw;
        }
    }
    restore_placeholders(content->cmd_str);
    lstadd_front(lexered_params, lstnew_p(content));
}

static void lexer_add_token(t_list **lexered_params, char c)
{
    t_lexer   		*content;

    if (!c)
        return ;
    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = c;
    content->cmd_str = NULL;
    content->dollar_array = NULL;
    lstadd_front(lexered_params, lstnew_p(content));
}

static void restore_placeholders(char *str)
{
    uint32_t            i;
    static const char   ph_table[3]
        = {0, '<', '>'}; //stesso ordine del .h

    i = -1;
    while (str[++i])
        if (str[i] < 0)
            str[i] = ph_table[-str[i]];
}

static bool is_token(char c)
{
    int8_t			        i;
	static const uint8_t	n_tokens = sizeof(g_tokens) / sizeof(g_tokens[0]);

	i = -1;
   	while (++i < n_tokens)
		if (g_tokens[i] == c)
			return (true);
	return (false);
}

void	del_content_lexer(void *content)
{
	t_lexer	*elem;

	elem = (t_lexer *)content;
	free(elem->cmd_str);
    free(elem->dollar_array);
    free(elem);
}
