/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:58:10 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 14:16:11 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

//str utils
int     ft_strlen(char *str);
void    ft_putstr_fd(char *s, int fd);
char	**ft_split(const char *s, char c);
//list utils
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
//tree utils
t_tree	*ft_treenew(int8_t type, char *cmd);
void    ft_treeadd_below(t_tree **head, t_tree *new);
t_tree	*ft_tree_last(t_tree *head);

#endif