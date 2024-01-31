/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:03:17 by craimond          #+#    #+#             */
/*   Updated: 2024/01/31 22:13:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

static t_token  lexer_get_token(char c);
static bool 	is_token(char *str, int *idx);
static t_lexer  *new_content_lexer(void);

t_list	*lexer(char *input)
{
    t_data          *data;
    int             i;
    t_lexer   		*content;
    t_list         	*lexered_params;

    data = get_data();
	lexered_params = NULL;
    data->lexered_params = &lexered_params;
    content = new_content_lexer();
    while (*input != '\0')
    {
        i = 0;
        while (input[i] && !is_token(input, &i))
            i++;
        if (i > 0)
        {
			content->cmd = (char *)malloc(sizeof(char) * (i + 1));
			if (!content->cmd)
				ft_quit(8, "failed to allocate memory");
            ft_strlcpy(content->cmd, input, i + 1);
			ft_lstadd_back(&lexered_params, ft_lstnew(content));
            content = new_content_lexer();
            input += i;
            i = 0;
        }
		if (*input != '\0')
		{
       	 	content->token = lexer_get_token(*input++);
            if (content->token == AND)
                input++;
            ft_lstadd_back(&lexered_params, ft_lstnew(content));
            content = new_content_lexer();
        }
    }
	return (lexered_params);
}

static  t_lexer *new_content_lexer(void)
{
    t_lexer	*content;

    content = (t_lexer *)malloc(sizeof(t_lexer));
    if (!content)
        ft_quit(8, "failed to allocate memory");
    content->cmd = NULL;
    content->token = 0;
    return (content);
}

static t_token lexer_get_token(char c)
{
    int8_t         	i;
	static uint8_t	n_tokens;
    static int8_t   tokens[7] = {PIPE, REDIR_R, REDIR_L, SEMICOLON, QUOTE, DQUOTE, AND};
    
	n_tokens = sizeof(tokens) / sizeof(tokens[0]);
    i = -1;
    while (++i < (n_tokens))
        if (tokens[i] == c)
            return (tokens[i]);
    return (0);
}

static bool is_token(char *str, int *idx)
{
    int8_t			i;
	static uint8_t	n_tokens;
    static char     tokens[7] = {PIPE, REDIR_R, REDIR_L, SEMICOLON, QUOTE, DQUOTE, AND};

    n_tokens = sizeof(tokens) / sizeof(tokens[0]);
	i = -1;
   	while (++i < n_tokens)
	{
		if (tokens[i] == str[*idx])
        {
            if (str[*idx] == AND && str[*idx + 1] != AND)
                return ((*idx)++, false);
			return (true);
        }
	}
	return (false);
}

void	del_content_lexer(void *content)
{
	t_lexer	*elem;

	elem = (t_lexer *)content;
	free(elem->cmd);
}
