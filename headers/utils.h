/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:58:10 by craimond          #+#    #+#             */
/*   Updated: 2024/03/02 00:29:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void    	ft_putstr_fd(char *s, int fd);
char    	*ft_strdup(char *s);
char	    **ft_strarrdup(char **arr);
char		**ft_split(char *s, char c);
char 		*ft_strtrim(char *s1, char *set);
uint32_t    ft_strlen(char *s);
char        *ft_strjoin(char *s1, char *s2);
char	    *ft_strnstr(char *big, char *little, size_t len);
char        *ft_strcpy(char *dst, char *src);
size_t	    ft_strlcpy(char *dst,  char *src, size_t size);
char 	    *ft_strcat(char *dst, char *src);
int	        ft_strncmp(char *s1, char *s2, size_t n);
int         ft_strcmp_lower(const char *s1, const char *s2);
int	        ft_strcmp(char *s1, char *s2);
char	    *ft_strchr(char *s, int c);
char        ft_tolower(char c);

void        *ft_calloc(size_t count, size_t size);
void        ft_freenull(void **ptr);
void	    ft_freematrix(char **matrix);
size_t	    ft_matrixsize(char **matrix);
int		    ft_isdigit(int c);
int 	    ft_atou(char *nptr);
char        *ft_utoa(unsigned int n);


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