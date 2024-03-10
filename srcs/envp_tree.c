/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:12:05 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 16:19:02 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_tree	*envp_tree_add(t_tree *const root, t_cc *const str)
{
	t_tree	*new;

	if (!root)
	{
		new = treenew(str, PERM);
		if (!new)
			panic(ERR_MEM, "minishell: failed to allocate memory");
		return (new);
	}
	if (ft_strcmp(str, (char *)root->content) < 0)
		root->left = envp_tree_add(root->left, str);
	else if (ft_strcmp(str, (char *)root->content) > 0)
		root->right = envp_tree_add(root->right, str);
	return (root);
}

t_tree	*envp_tree_remove(t_tree *const root,
	t_cc *const name, const uint16_t name_len)
{
	t_tree	*tmp;

	if (!root)
		return (NULL);
	if (ft_strncmp(name, (char *)root->content, name_len) < 0)
		root->left = envp_tree_remove(root->left, name, name_len);
	else if (ft_strncmp(name, (char *)root->content, name_len) > 0)
		root->right = envp_tree_remove(root->right, name, name_len);
	else
	{
		if (!root->left || !root->right)
		{
			if (!root->left)
				tmp = root->right;
			else
				tmp = root->left;
			return (free(root), tmp);
		}
		tmp = treefirst(root->right);
		root->content = tmp->content;
		root->right = envp_tree_remove(root->right,
				(char *)tmp->content, name_len);
	}
	return (root);
}

t_tree	*envp_tree_find(const t_tree *const root,
	t_cc *const name, const uint16_t name_len)
{
	if (!root)
		return (NULL);
	if (ft_strncmp(name, (char *)root->content, name_len) < 0)
		return (envp_tree_find(root->left, name, name_len));
	else if (ft_strncmp(name, (char *)root->content, name_len) > 0)
		return (envp_tree_find(root->right, name, name_len));
	return ((t_tree *)root);
}

void	envp_print_export(const t_tree *const root)
{
	char	*env_name;
	char	*env_value;
	char	*tmp;
	char	*sep;

	if (!root)
		return ;
	tmp = ft_strdup((char *)root->content, TMP);
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
	envp_print_export(root->left);
	envp_print_export(root->right);
}
