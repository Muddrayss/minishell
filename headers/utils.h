/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 08:58:10 by craimond          #+#    #+#             */
/*   Updated: 2024/02/02 11:41:29 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

typedef struct s_list
{
    void			*content;
    struct s_list	*next;
    struct s_list	*prev;
}					t_list;

//list utils
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
//tree utils
t_tree	*ft_treenew(int8_t type, char *cmd);
void    ft_treeadd_below(t_tree **head, t_tree *new);
t_tree	*ft_tree_last(t_tree *head);

#endif