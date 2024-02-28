/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/02/28 12:46:08 by craimond         ###   ########.fr       */
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
# include <dirent.h>

# include "builtins.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"
# include "envp_utils.h"
# include "utils.h"
# include "protected_methods.h"
# include "errors.h"
# include "colors.h"

typedef struct s_data
{
	char	*cmd_path;
	char	**cmd_args;
	t_list	**envp_table;
	char	**envp_matrix;
	char	*starting_dir;
	t_list	**lexered_params;
	t_tree  **parsed_params;
	char 	*input;
	pid_t 	main_pid;
}t_data;

extern int g_status;

# define MAX(a, b) (a * (a > b) + b * (a <= b))
# define MAX_FDS 1024

void	check_args(int argc, char **argv);
void	init_data(char **envp);
void    init_general(void);
t_data	*get_data(void);
void	ft_quit(uint8_t id, char *msg);
void    free_data(void);
bool    is_shell_space(char c);
bool 	is_quote(char c);
bool 	is_empty_str(char *str);
void	*cxmalloc(size_t size); // TODO: to remove

//#define malloc(x)    cxmalloc(x)
#endif