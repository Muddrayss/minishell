/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:12:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/01 18:39:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_envp_tree *envp_tree_new(char *str)
{
    t_envp_tree  *new;

    new = (t_envp_tree *)malloc_p(sizeof(t_envp_tree));
    new->str = str;
    new->left = NULL;
    new->right = NULL;
    return (new);
}

t_envp_tree *envp_tree_add(t_envp_tree *root, char *str)
{
    if (!root)
        return (envp_tree_new(str));
    if (ft_strcmp(str, root->str) < 0)
        root->left = envp_tree_add(root->left, str);
    else if (ft_strcmp(str, root->str) > 0)
        root->right = envp_tree_add(root->right, str);
    return (root);
}

t_envp_tree *envp_tree_findmin(t_envp_tree *root)
{
    if (!root)
        return (NULL);
    while (root->left)
        root = root->left;
    return (root);
}

t_envp_tree *envp_tree_remove(t_envp_tree *root, char *name, uint16_t name_len)
{
    t_envp_tree *tmp;

    if (!root)
        return (NULL);
    if (ft_strncmp(name, root->str, name_len) < 0)
        root->left = envp_tree_remove(root->left, name, name_len);
    else if (ft_strncmp(name, root->str, name_len) > 0)
        root->right = envp_tree_remove(root->right, name, name_len);
    else
    {
        if (root->left == NULL)
            return (root->right);
        else if (root->right == NULL)
            return (root->left);
        tmp = envp_tree_findmin(root->right);
        root->str = tmp->str;
        root->right = envp_tree_remove(root->right, tmp->str, name_len);
    }
    return (root);
}

t_envp_tree *envp_tree_find(t_envp_tree *root, char *name, uint16_t name_len)
{
    if (!root)
        return (NULL);
    if (ft_strncmp(name, root->str, name_len) < 0)
        return (envp_tree_find(root->left, name, name_len));
    else if (ft_strncmp(name, root->str, name_len) > 0)
        return (envp_tree_find(root->right, name, name_len));
    return (root);
}

void envp_tree_clear(t_envp_tree *root)
{
    if (!root)
        return ;
    envp_tree_clear(root->left);
    envp_tree_clear(root->right);
    free(root);
}

void envp_print_export(t_envp_tree *root)
{
    char    *env_name;
    char    *env_value;
    char    *tmp;
    char    *sep;

    if (!root)
        return ;
    tmp = ft_strdup(root->str);
    if (!tmp)
        ft_quit(ERR_MEM, "minishell: failed to allocate memory");
    sep = ft_strchr(tmp, '=');
    if (sep)
    {
        *sep = '\0';
        env_value = sep + 1;
    }
    else
        env_value = "";
    env_name = tmp;
    printf("declare -x %s=\"", env_name);
    printf("%s\"\n", env_value);
    free(tmp);
    envp_print_export(root->left);
    envp_print_export(root->right);
}
