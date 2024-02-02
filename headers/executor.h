/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:46:26 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 18:52:39 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# define EXEC_FAILURE 1
# define COMMAND_NOT_FOUND 127

# define FIRST_CMD 0
# define SECOND_CMD 1

void    executor(t_list *parsed_params);
void    create_heredocs(t_tree *tree, uint32_t heredoc_fileno1);
int     get_matching_heredoc(int id1, int id2);
void    replace_env_vars(char **str);
bool    check_last_subcmd(char *cmd_str);

#endif