/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/01/25 15:22:07 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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

typedef struct s_data
{
	char	*cmd_path;
	char	**cmd_args;
	char	**envp;
	char	*starting_dir;
	t_list	**lexered_params;
}			t_data;

typedef struct s_signals
{
	int sigint;
	int in_cmd;
	int in_heredoc;
}				t_signals;
extern t_signals	g_signals;

# include "colors.h"
# include "error.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"

# define MAX(a, b) (a * (a > b) + b * (a <= b))

char		*get_cmd(char *path, char *cmd, t_data *data);
void		exec_simple_cmd(char *path, char *cmd_str, t_data *data);
void  		exec(char *path, char *cmd_str, t_data *data);
void		free_matrix(char **matrix);
void clean_heredocs(t_data *data);
void ft_quit(int id, char *msg, t_data *data);
void 		free_data(t_data *data);
int8_t 		ft_parse_error(char token);
bool		is_shell_space(char c);
void		init_signals(void);
void		ft_lstdel_if(t_list **lst, bool (*f)(void *), void (*del)(void *));

#endif