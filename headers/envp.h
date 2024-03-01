/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:21:31 by egualand          #+#    #+#             */
/*   Updated: 2024/03/01 16:15:08 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define HASH_TABLE_SIZE 255  //non 256 altrimenti va in loop infinito envp_table_clear
# define REMOVE -1
# define REPLACE 0
# define ADD 1

// uint8_t hash(char *str);

void    	envp_init(char **envp);
void	    ft_setenv(char *env_name, char *env_value, bool replace);
char	    *ft_getenv(char *env_name);
void	    ft_unsetenv(char *env_name);

typedef struct s_envp_tree
{
	char				*str;
	struct s_envp_tree	*left;
	struct s_envp_tree	*right;
}t_envp_tree;

t_envp_tree *envp_tree_new(char *str);
t_envp_tree *envp_tree_add(t_envp_tree *root, char *str);
t_envp_tree *envp_tree_find(t_envp_tree *root, char *name, uint16_t name_len);
t_envp_tree *envp_tree_findmin(t_envp_tree *root);
t_envp_tree *envp_tree_remove(t_envp_tree *root, char *name, uint16_t name_len);
void 		envp_tree_clear(t_envp_tree *root);
void        envp_print_export(t_envp_tree *root);

void	envp_matrix_remove(char *env_name, uint32_t name_len);
void	envp_matrix_add(char *str);
void	envp_print_env(void);

#endif