/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:26 by craimond          #+#    #+#             */
/*   Updated: 2024/02/27 17:24:06 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define EXEC_FAILURE   1
# define CMD_NOT_FOUND  127

void    executor(t_tree *parsed_params);
void    create_heredocs(t_tree *tree, int *status);
char    *get_heredoc_filename(int32_t id);
bool    check_last_subcmd(char *cmd_str);
char    *replace_wildcards(char *str);
char    *replace_env_vars(char *str); //TODO flag per heredoc perche' non deve guardare le quotes
char    *clear_quotes(char *str);
void    exec_simple_cmd(char *path, char *cmd_str);
void    exec(char *path, char *cmd_str);
char    *get_cmd_path(char *path, char *cmd);

#endif
