/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:37:03 by craimond          #+#    #+#             */
/*   Updated: 2024/03/06 16:29:52 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void    *gc_get(uint8_t **const flags_array);

void	gc_add(const void *const ptr, const uint8_t type)
{
	void		**gc;
	uint8_t		*gc_flags;
	size_t		i;
	size_t	 	max_size;

	if (!ptr)
		return ;
	max_size = RAM_SIZE / sizeof(void *);
	gc = gc_get(&gc_flags);
	i = 0;
	while (gc[i] && i < max_size - 1)
		i++;
	if (i >= max_size - 1)
		ft_quit(ERR_MEM, "minishell: failed to allocate memory (NO MORE AVAILABLE SPACE)");
	gc[i] = (void *)ptr;
	gc_flags[i] = type;
}

void	gc_remove(void *ptr)
{
	void		**gc;
	uint16_t	i;

	if (!ptr)
		return ;
	gc = gc_get(NULL);
	i = 0;
	while (gc[i])
	{
		if (gc[i] == ptr)
		{
			free(gc[i]);
			gc[i] = NULL;
			break ;
		}
		i++;
	}
}

void	gc_clear_type(const uint8_t type)
{
	void		**gc;
	uint8_t		*gc_flags;
	uint16_t	i;

	gc = gc_get(&gc_flags);
	i = 0;
	while (gc[i])
	{
		if (type == 3 || gc_flags[i] == type)
		{
			free(gc[i]);
			gc[i] = NULL;
		}
		i++;
	}
	if (type == 3)
	{
		free(gc);
		free(gc_flags);
	}
}

static void    *gc_get(uint8_t **const flags_array)
{
	static void		**gc;
	static uint8_t	*gc_flags;

	if (!gc)
	{
		gc = ft_calloc(RAM_SIZE / sizeof(void *), sizeof(void *));
		gc_flags = malloc(RAM_SIZE / sizeof(void *));
	}
	if (flags_array)
		*flags_array = gc_flags;
	return (gc);
}