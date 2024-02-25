/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/02/25 19:10:39 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool 	is_token(char c);
static void 	lexer_add_cmd(t_list **lexered_params, uint32_t cmd_len, char *input);
static void 	lexer_add_token(t_list **lexered_params, char c);


void print_lexered_params(t_list *lexered_params)
{
    t_lexer *elem;

    while (lexered_params)
    {
        elem = (t_lexer *)lexered_params->content;
        if (elem->token)
            printf("token: %c\n", elem->token);
        else
            printf("cmd_str: %s\n", elem->cmd_str);
        lexered_params = lexered_params->next;
    }
}

t_list	*lexer(char *input)
{
    uint32_t        cmd_len;
    char            current_quote;
    t_list         	**lexered_params;

	lexered_params = (t_list **)malloc_p(sizeof(t_list *));
    *lexered_params = NULL;
    current_quote = '\0';
    get_data()->lexered_params = lexered_params;
    cmd_len = 0;
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
            if (cmd_len > 0)
                lexer_add_cmd(lexered_params, cmd_len, input - cmd_len);
            lexer_add_token(lexered_params, *input);
            cmd_len = 0;
        }
        else
            cmd_len++;
        input += *input != '\0';
    }
    lstreverse(lexered_params);
    print_lexered_params(*lexered_params);
    return (*lexered_params);
}

static void lexer_add_cmd(t_list **lexered_params, uint32_t cmd_len, char *input)
{
    int32_t         i;
    int32_t         j;
    int32_t         k;
    int32_t         n_dollars;
    int32_t         n_redirs;
    t_lexer   		*content;
    char            master_quote;

    master_quote = '\0';
    content = (t_lexer *)malloc_p(sizeof(t_lexer));
    content->token = 0;
    content->cmd_str = (char *)malloc_p(sizeof(char) * (cmd_len + 1));
    n_dollars = 0;
    n_redirs = 0;
    i = -1;
    while (input[++i])
    {
        n_dollars += (input[i] == '$');
        n_redirs += (input[i] == '>' || input[i] == '<');
    }
    content->dollar_array = (bool *)malloc_p(sizeof(bool) * (n_dollars + 1));
    content->redirs_array = (bool *)malloc_p(sizeof(bool) * (n_redirs + 1));
    i = 0;
    j = 0;
    k = 0;
    while (cmd_len--)
    {
        if (*input == '\'' || *input == '"')
        {
            if (!master_quote)
                master_quote = *input;
            else if (master_quote == *input)
                master_quote = '\0';
            content->cmd_str[i++] = *input;
        }
        else
        {
            if (*input != master_quote)
                content->cmd_str[i++] = *input;
            if (*input == '$')
            {
                if (master_quote == '\'' || !master_quote)
                    content->dollar_array[j++] = true;
                else
                    content->dollar_array[j++] = false;
            }
            else if (*input == '>' || *input == '<')
                content->redirs_array[k++] = true;
        }
        input++;
    }
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

static bool is_token(char c)
{
    int8_t			i;
    static char     tokens[5] = {'|', ';', '&', '(', ')'};
	static uint8_t	n_tokens = sizeof(tokens) / sizeof(tokens[0]);

	i = -1;
   	while (++i < n_tokens)
		if (tokens[i] == c)
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
