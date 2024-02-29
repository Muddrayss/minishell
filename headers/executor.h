/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:26 by craimond          #+#    #+#             */
/*   Updated: 2024/02/29 15:40:34 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define EXEC_FAILURE   1
# define CMD_NOT_FOUND  127

void    executor(t_tree *parsed_params);
void    create_heredocs(t_tree *tree, int *status);
char    *get_heredoc_filename(int32_t id);
void    exec_redirs(t_list *redirs);
char    *get_cmd_path(char *path, char *cmd);
char 	*replace_env_vars(char *str, bool ignore_quotes);
// char    *replace_env_vars_heredoc(char *str);
char 	*replace_wildcards(char *str);
char	*clear_quotes(char *str);
void    exec(char *path, char *cmd_str);
void	exec_simple_cmd(char *path, char *cmd_str);

#endif
