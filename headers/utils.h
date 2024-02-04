/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:58:10 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 20:22:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void    ft_putstr_fd(char *s, int fd);
char    *ft_strdup(const char *s);
char	**ft_strarr_dup(char **arr);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
char    *ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char    *ft_strcpy(char *dst, const char *src);
char    *ft_strcat(char *dst, const char *src);

void    *ft_calloc(size_t count, size_t size);
void	ft_freematrix(char **matrix);

t_list	*lstnew_p(void *content);
void	lstadd_back(t_list **lst, t_list *new);
t_list	*lstlast(t_list *lst);
void	lstclear(t_list **lst, void (*del)(void *));

t_tree	*treenew_p(int8_t type, char *cmd);
void    treeadd_below(t_tree **head, t_tree *new);
t_tree	*tree_last(t_tree *head);
void    treeclear(t_tree **head, void (*del)(void *));

#endif