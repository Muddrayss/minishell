/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:26 by craimond          #+#    #+#             */
/*   Updated: 2024/01/30 21:20:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define EXEC_FAILURE 1
# define COMMAND_NOT_FOUND 127

void    executor(t_list *parsed_params);
void    create_heredocs(t_list *parsed_params);
bool    is_heredoc(t_list *redirs);
int     get_matching_heredoc(int id1, int id2);
void    replace_env_vars(char **str);
bool    check_last_subcmd(char *cmd_str);

#endif