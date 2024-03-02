/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:21:31 by egualand          #+#    #+#             */
/*   Updated: 2024/03/01 23:57:55 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# define HASH_TABLE_SIZE 255  //non 256 altrimenti va in loop infinito envp_table_clear
# define REMOVE -1
# define REPLACE 0
# define ADD 1

// uint8_t hash(char *str);

void  	envp_init(char **envp);
void	ft_setenv(char *env_name, char *env_value, bool replace);
char    *ft_getenv(char *env_name);
void	ft_unsetenv(char *env_name);

t_tree	*envp_tree_add(t_tree *root, char *str);
t_tree	*envp_tree_remove(t_tree *root, char *name, uint16_t name_len);
t_tree	*envp_tree_find(t_tree *root, char *name, uint16_t name_len);
void	envp_tree_print(t_tree *root);
void	envp_tree_print_export(t_tree *root);

void	envp_matrix_remove(char *env_name, uint32_t name_len);
void	envp_matrix_add(char *str);
void	envp_print_env(void);
void	envp_print_export(t_tree *root);

#endif