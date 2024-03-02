/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:26 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 00:07:10 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define EXEC_FAILURE   1
# define CMD_NOT_FOUND  127

void    executor(t_tree *parsed_params);
void    create_heredocs(t_tree *tree, uint8_t *status);
char    *get_heredoc_filename(uint16_t id);
void    exec_redirs(t_list *redirs);
char    *get_cmd_path(char *path, char *cmd);
char    **get_cmd_args(char *cmd_str);
void    replace_env_vars(char **str, bool ignore_quotes);
void    replace_wildcards(char **str);
void    clear_quotes(char **str);
void    exec(char *path, char *cmd_str);
void	exec_simple_cmd(char *path, char *cmd_str);

#endif
