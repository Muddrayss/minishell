# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 17:09:33 by craimond          #+#    #+#              #
#    Updated: 2024/03/01 16:18:01 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LEXER_SRCS = $(addprefix lexer/, lexer.c lexer_utils.c)
PARSER_UTILS = $(addprefix parser_utils/, general_utils.c merge_separators.c check_syntax.c)
PARSER_REDIRS = $(addprefix parser_redirs/, fill_redirs.c clear_redirs.c)
PARSER_SRCS = $(addprefix parser/, parser.c $(PARSER_REDIRS) $(PARSER_UTILS))
EXECUTOR_UTILS = $(addprefix executor_utils/, general_utils.c get_cmd_path.c replace_env_vars.c replace_wildcards.c)
EXECUTOR_SRCS = $(addprefix executor/, executor.c executor_heredoc.c executor_redirs.c $(EXECUTOR_UTILS))
BUILTIN_SRCS = $(addprefix builtins/, builtins_handler.c ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c)
GENERAL_SRCS = minishell.c minishell_init.c minishell_exit.c minishell_utils.c envp_tree.c envp_matrix.c envp_utils.c signals.c conditionals.c xmalloc.c
GENERAL_UTILS_SRCS = $(addprefix general/, ft_freematrix.c ft_atou.c ft_isdigit.c ft_matrixsize.c ft_utoa.c ft_calloc.c)
LST_UTILS_SRCS = $(addprefix lst/, lstadd_front.c lstadd_back.c lstlast.c lstclear.c lstreverse.c lstnew_p.c lstremoveone.c lstdelone.c lstdelif.c)
STR_UTILS_SRCS = $(addprefix str/, ft_putstr_fd.c ft_split.c ft_strtrim.c ft_strdup.c ft_strarrdup.c ft_strjoin.c ft_strlen.c ft_strcat.c ft_strcpy.c ft_strlcpy.c ft_strnstr.c ft_strncmp.c ft_strcmp.c ft_strcmp_lower.c ft_strchr.c ft_tolower.c)
TREE_UTILS_SRCS = $(addprefix tree/, tree_size.c treeadd_below.c treeclear.c treenew_p.c)
PROTECTED_METHODS_SRCS = $(addprefix protected_methods/, alloc.c dirs.c dup.c files.c processes.c signals.c wait.c utils.c)
UTILS_SRCS = $(addprefix utils/, $(GENERAL_UTILS_SRCS) $(STR_UTILS_SRCS) $(LST_UTILS_SRCS) $(TREE_UTILS_SRCS) $(PROTECTED_METHODS_SRCS))

SRCS = $(addprefix srcs/, $(GENERAL_SRCS) $(LEXER_SRCS) $(PARSER_SRCS) $(EXECUTOR_SRCS)  $(BUILTIN_SRCS) $(UTILS_SRCS))		
OBJS = $(SRCS:.c=.o)
HEADERS = $(addprefix headers/, minishell.h lexer.h parser.h executor.h signals.h envp.h utils.h protected_methods.h colors.h)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g #TODO remove -g
RM = rm -f

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p tmp
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@echo "Compilation of $(NAME) done!"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r tmp
	@$(RM) $(OBJS)
	@echo "Cleaning of $(NAME) done!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Full cleaning of $(NAME) done!"

leaks: all
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME) 2> leak_report
	@echo "leak report generated"
	@clean

re: fclean all

.PHONY: all clean fclean re
