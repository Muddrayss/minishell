/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:58:10 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 19:52:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

int     ft_strlen(char *str);
void    ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *s, char c);
t_list	*lstnew(void *content);
void	lstadd_back(t_list **lst, t_list *new);
t_list	*lstlast(t_list *lst);
t_tree	*treenew(int8_t type, char *cmd);
void    treeadd_below(t_tree **head, t_tree *new);
t_tree	*tree_last(t_tree *head);

#endif