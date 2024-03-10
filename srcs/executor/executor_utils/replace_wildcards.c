/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egualand <egualand@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:05:44 by craimond          #+#    #+#             */
/*   Updated: 2024/03/10 15:02:44 by egualand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_list	*parse_patn(t_cc *const patn, t_cc *const cwd, const bool is_r);
static char		*get_full_entry(t_cc *basedir, t_cc *const entry,
					t_cc *cwd, const bool is_r);
static bool		matches_patn(t_cc *patn, const struct dirent *const entry,
					const uint16_t idx);
static char		*get_new_patn(t_cc *const basedir, t_cc *patn,
					t_cc *const entry);

//TODO non funziona /*/*/*
void	replace_wildcards(char **const str)
{
	t_list				*matching_files;
	char				*patn;
	uint16_t			idx;
	uint16_t			len;
	t_cc *const			cwd = getcwd_p(NULL, 0, TMP);

	idx = 0;
	patn = get_patn(*str, &idx, &len);
	while (patn)
	{
		patn = add_cwd(patn, cwd);
		matching_files = parse_patn(patn, cwd, false);
		matching_files = sort_result(matching_files);
		*str = insert_result(*str, matching_files, idx, len);
		idx += len;
		patn = get_patn(*str, &idx, &len);
	}
}

static t_list	*parse_patn(t_cc *patn, t_cc *const cwd, const bool is_r)
{
	struct dirent		*entry;
	t_list				*matching_files;
	char				*new_patn;
	char				*full_entry;
	t_dir				dir;

	dir.basedir = get_base_dir(&patn, (bool *)&is_r);
	dir.dir = opendir_p(dir.basedir);
	matching_files = NULL;
	while (dir.dir)
	{
		entry = readdir_p(dir.dir);
		if (!entry)
			break ;
		if (entry->d_name[0] == '.' || !matches_patn(patn, entry, 0))
			continue ;
		full_entry = get_full_entry(dir.basedir, entry->d_name, cwd, is_r);
		new_patn = get_new_patn(dir.basedir, patn, entry->d_name);
		if (!new_patn)
			lstadd_front(&matching_files, lstnew(full_entry, TMP));
		else
			lstadd_back(&matching_files, parse_patn(new_patn, cwd, is_r));
	}
	return (closedir((DIR *)dir.dir), matching_files);
}

static char	*get_full_entry(t_cc *basedir, t_cc *const entry,
				t_cc *cwd, const bool is_r)
{
	char	*full_entry;

	while (*cwd && *basedir == *cwd)
	{
		basedir++;
		cwd++;
	}
	if (*basedir == '/')
		basedir++;
	full_entry = (char *)calloc_p(ft_strlen(basedir)
			+ ft_strlen(entry) + 2 + is_r, sizeof(char), TMP);
	if (is_r)
		ft_strcat(full_entry, "/");
	if (*basedir)
	{
		ft_strcat(full_entry, basedir);
		ft_strcat(full_entry, "/");
	}
	ft_strcat(full_entry, entry);
	return (full_entry);
}

static bool	matches_patn(t_cc *patn,
				const struct dirent *const entry, const uint16_t idx)
{
	if (entry->d_name[idx] == '\0')
	{
		while (*patn == '*')
			patn++;
		return (*patn == '\0' || (*patn == '/' && entry->d_type == DT_DIR));
	}
	if (*patn == '*')
		return (matches_patn(patn + 1, entry, idx)
			|| matches_patn(patn, entry, idx + 1));
	if (*patn == entry->d_name[idx])
		return (matches_patn(patn + 1, entry, idx + 1));
	return (false);
}

static char	*get_new_patn(t_cc *const basedir, t_cc *patn, t_cc *const entry)
{
	char		*new_patn;
	uint16_t	size;

	patn = ft_strchr(patn, '/');
	if (!patn)
		return (NULL);
	size = ft_strlen(basedir) + ft_strlen(entry) + ft_strlen(patn) + 3;
	new_patn = (char *)calloc_p(size, sizeof(char), TMP);
	ft_strcpy(new_patn, basedir);
	ft_strcat(new_patn, "/");
	ft_strcat(new_patn, entry);
	ft_strcat(new_patn, patn);
	return (new_patn);
}
