/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:58:10 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 00:18:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void    	ft_putstr_fd(char *s, uint16_t fd);
char    	*strdup_p(char *s);
char        *ft_strtok(char *str, char sep);
char 		*strtrim_p(char *s1, char *set);
uint16_t    ft_strlen(const char *s);
char        *strjoin_p(char *s1, char *s2);
char	    *ft_strnstr(const char *big, const char *little, uint16_t len);
char        *ft_strcpy(char *dst, char *src);
uint16_t	ft_strlcpy(char *dst,  char *src, uint16_t size);
char 	    *ft_strcat(char *dst, char *src);
int16_t	    ft_strcmp(const char *s1, const char *s2);
int16_t	    ft_strncmp(char *s1, char *s2, uint16_t n);
int16_t     ft_strcmp_lower(const char *s1, const char *s2);
char	    *ft_strchr(char *s, char c);
char        ft_tolower(char c);

void        *ft_calloc(size_t count, size_t size);
void        free_and_null(void **ptr);
void	    ft_freematrix(char **matrix);
uint16_t	ft_matrixsize(char **matrix);
bool		ft_isdigit(char c);
int32_t     ft_atoi(char *str);
char        *ft_itoa(int32_t n);

t_list	    *lstnew_p(void *content);
void	    lstadd_front(t_list **lst, t_list *new);
t_list	    *lstlast(t_list *lst);
void        lstadd_back(t_list **lst, t_list *new);
void        lstreverse(t_list **lst);
void	    lstclear(t_list **lst, void (*del)(void *));
void	    lstdelone(t_list *lst, void (*del)(void *));
void        lstremoveone(t_list **head, t_list *to_remove, void (*del)(void *));
void	    lstdelif(t_list **lst, bool (*f)(void *), void (*del)(void *));

t_tree	    *treenew_p(void *content);
t_tree      *treeadd_below(t_tree *node, t_tree *new);
t_tree      *tree_first(t_tree *root);
void	    treeclear(t_tree **tree, void (*del)(void *));

#endif