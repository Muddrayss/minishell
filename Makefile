# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 17:09:33 by craimond          #+#    #+#              #
#    Updated: 2024/02/02 13:55:58 by craimond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES_DIR = .

SRCS = minishell.c minishell_utils.c lexer.c signals.c parser.c executor.c executor_utils.c heredoc.c $(addprefix utils/, str_utils lst_utils.c tree_utils.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(addprefix headers/, minishell.h lexer.h parser.h executor.h signals.h utils.h colors.h)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #TODO remove -g
RM = rm -f

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@mkdir -p tmp
	@$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDES_DIR) -L $(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@echo "Compilation of $(NAME) done!"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean:
	@$(RM) -r tmp
	@$(RM) $(OBJS)
	@echo "Cleaning of $(NAME) done!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Full cleaning of $(NAME) done!"

leaks: all
	@printf "{\n readline\n Memcheck:Leak\n fun:rl_parse_and_bind\n fun:readline_internal_teardown\n fun:rl_initialize\n fun:readline\n}" > readline.supp
	@valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp -v ./$(NAME) 2> leak_report
	@echo "leak report generated"

re: fclean all

.PHONY: all clean fclean re
