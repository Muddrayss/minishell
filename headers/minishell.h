/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 09:38:50 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <limits.h>

# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"
# include "envp_utils.h"
# include "utils.h"
# include "protected_methods.h"
# include "colors.h"

typedef struct s_data
{
	char	*cmd_path;
	char	**cmd_args;
	t_list	*envp_table;
	char	**envp_matrix;
	char	*starting_dir;
	t_list	**lexered_params;
}t_data;

extern int g_status;

# define MAX(a, b) (a * (a > b) + b * (a <= b))

t_data		*get_data(void);
char		*get_cmd(char *path, char *cmd);
void		exec_simple_cmd(char *path, char *cmd_str);
void  		exec(char *path, char *cmd_str);
void		free_matrix(char **matrix);
void 		clean_heredocs();
void 		ft_quit(int id, char *msg);
void 		free_data(t_data *data);
void 		ft_parse_error(char token);
bool		is_shell_space(char c);

#endif
