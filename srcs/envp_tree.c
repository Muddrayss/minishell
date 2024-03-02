/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:12:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 15:03:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_tree *envp_tree_add(t_tree *root, char *str)
{
    if (!root)
        return (treenew_p(str));
    if (ft_strcmp(str, (char *)root->content) < 0)
        root->left = envp_tree_add(root->left, str);
    else if (ft_strcmp(str, (char *)root->content) > 0)
        root->right = envp_tree_add(root->right, str);
    return (root);
}

t_tree *envp_tree_remove(t_tree *root, char *name, uint16_t name_len)
{
    t_tree  *tmp;

    if (!root)
        return (NULL);
    if (ft_strncmp(name, (char *)root->content, name_len) < 0)
        root->left = envp_tree_remove(root->left, name, name_len);
    else if (ft_strncmp(name, (char *)root->content, name_len) > 0)
        root->right = envp_tree_remove(root->right, name, name_len);
    else
    {
        if (root->left == NULL)
            return (root->right);
        else if (root->right == NULL)
            return (root->left);
        tmp = tree_first(root->right);
        root->content = tmp->content;
        root->right = envp_tree_remove(root->right, (char *)tmp->content, name_len);
    }
    return (root);
}

t_tree *envp_tree_find(t_tree *root, char *name, uint16_t name_len)
{
    if (!root)
        return (NULL);
    if (ft_strncmp(name, (char *)root->content, name_len) < 0)
        return (envp_tree_find(root->left, name, name_len));
    else if (ft_strncmp(name, (char *)root->content, name_len) > 0)
        return (envp_tree_find(root->right, name, name_len));
    return (root);
}

void envp_print_export(t_tree *root)
{
    char    *env_name;
    char    *env_value;
    char    *tmp;
    char    *sep;

    if (!root)
        return ;
    tmp = strdup_p((char *)root->content);
    sep = ft_strchr(tmp, '=');
    if (sep)
    {
        *sep = '\0';
        env_value = sep + 1;
    }
    else
        env_value = "";
    env_name = tmp;
    printf("declare -x %s", env_name);
    if (env_value && *env_value)
        printf("=\"%s\"", env_value);
    printf("\n");
    free_and_null((void **)&tmp);
    envp_print_export(root->left);
    envp_print_export(root->right);
}
