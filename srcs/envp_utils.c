/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:46:00 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 17:31:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

//envp_matrix e envp_tree condividono le stesse stringhe (stesse malloc)
//envp_matrix_remove fa la free, envp_tree_remove no (quindi e' IMPORTANTE L'ORDINE di chiamata)

void    envp_init(char **envp)
{
    uint16_t    size;
    t_data      *data;
    char        **matrix;
    t_envp_tree *tree;

    data = get_data();
    tree = NULL;
    size = ft_matrixsize(envp);
    matrix = malloc_p(sizeof(char *) * (size + 1));
    matrix[size] = NULL;
    while (size--)
    {
        tree = envp_tree_add(tree, envp[size]);
        matrix[size] = ft_strdup(envp[size]);
        if (!matrix[size])
        {
            ft_freematrix(matrix);
            ft_quit(ERR_MEM, "minishell: failed to allocate memory");
        }
    }
    data->envp_tree = tree;
    data->envp_matrix = matrix;
}

//NAME DEVE ESSERE COMPRESO DI '='
void	ft_setenv(char *name, char *value, bool replace)
{
    char        *str;

    str = ft_strjoin(name, value);
    if (!str)
        ft_quit(ERR_MEM, "minishell: failed to allocate memory");
    if (replace)
        ft_unsetenv(name);
    envp_tree_add(get_data()->envp_tree, str);
    envp_matrix_add(str);
}

//NAME DEVE ESSERE COMPRESO DI '='
void	ft_unsetenv(char *name)
{
    uint16_t    name_len;

    name_len = ft_strlen(name);
    envp_tree_remove(get_data()->envp_tree, name, name_len);
    envp_matrix_remove(name, name_len);
}

//NAME DEVE ESSERE COMPRESO DI '='
char	*ft_getenv(char *name)
{
    t_envp_tree *found;
    char        *value;

    found = envp_tree_find(get_data()->envp_tree, name, ft_strlen(name));
    if (found)
    {
        value = ft_strchr(found->str, '=');
        if (value)
            return (value + 1);
        else
            return (NULL);
    }
    return (NULL);
}
