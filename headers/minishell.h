/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:09:20 by craimond          #+#    #+#             */
/*   Updated: 2024/03/04 00:25:14 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//TODO trovare un modo per evitare il casting su free_and_null

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

typedef struct s_list
{
    void			*content;
    struct s_list	*next;
    struct s_list	*prev;
}t_list;

typedef struct s_tree
{
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}t_tree;

# include "builtins.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "signals.h"
# include "envp.h"
# include "utils.h"
# include "protected_methods.h"
# include "errors.h"
# include "colors.h"

typedef struct s_data
{
	char		**cmd_args;
	t_tree		*envp_tree;
	char		**envp_matrix;
	uint16_t	envp_size;
	char		*starting_dir;
	t_list		*lexered_params;
	t_tree  	*parsed_params;
	char 		*input;
	pid_t 		main_pid;
}t_data;

extern uint8_t g_status;

# define MAX(a, b) (a * (a > b) + b * (a <= b))
# define MAX_FDS 1024

void	check_args(const int argc, const char **const argv, const char **const envp);
void	init_data(const char **const envp);
void    init_general(void);
t_data	*get_data(void);
void	ft_quit(const uint8_t id, const char *const msg);
void    free_data(void);
bool    is_shell_space(const char c);
bool 	is_quote(const char c);
bool 	is_redir(const char c);
bool 	is_empty_str(const char *str);
void	*cxmalloc(size_t size); // TODO: to remove

//#define malloc(x)    cxmalloc(x)
#endif