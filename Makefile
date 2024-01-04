# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 17:09:33 by craimond          #+#    #+#              #
#    Updated: 2024/01/04 18:58:02 by egualand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES_DIR = .

SRCS = 	minishell.c minishell_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

NAME = minishell

LIBFT = libft.a
LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/$(LIBFT)

all: $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS) -I $(INCLUDES_DIR) -L $(LIBFT_DIR) -lft -o $(NAME)
	@echo "Compilation of $(NAME) done!"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Cleaning of $(NAME) done!"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Full cleaning of $(NAME) done!"

re: fclean all

.PHONY: all clean fclean re