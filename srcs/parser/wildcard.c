/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:22:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/16 19:15:24 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char     *get_wildcard_str(char *str, uint32_t *idx);
static char     *get_new_wildcard_str(char *basedir, char *entry, char *wildcard_str);
static char     *get_base_dir(char *wildcard_str);
static t_list   *parse_wildcard_str(char *wildcard_str);
static bool     matches_pattern(char *pattern, char *entry);

void    replace_wildcards(char *str)
{
    char        *wildcard_str;
    t_list      *matching_files;
    uint32_t    idx;

    while (true)
    {
        idx = 0;
        wildcard_str = get_wildcard_str(str, &idx);
        if (!wildcard_str)
            break ;
        matching_files = parse_wildcard_str(wildcard_str);
        ft_lstreverse(&matching_files);
        str = insert_wildcards(str, matching_files, idx); //deve fare il free di str
        free(wildcard_str);
    }
    return (str);
}

static t_list   *parse_wildcard_str(char *wildcard_str)
{
    char            *basedir;
    char            *new_wildcard_str;
    t_list          *matching_files;
    DIR             *dir;
    char            *end;
    struct dirent   *entry;

    matching_files = NULL;
    basedir = get_base_dir(wildcard_str);
    wildcard_str = ft_strchr(wildcard_str, '/') + 1;
    dir = opendir(basedir);
    entry = readdir(dir);
    while (entry)
    {
        if (matches_pattern(wildcard_str, entry->d_name) == true)
        {
            new_wildcard_str = get_new_wildcard_str(basedir, wildcard_str, entry->d_name);
            ft_lstadd_front(&matching_files, parse_wildcard_str(new_wildcard_str));
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return (matching_files);
}

static bool matches_pattern(char *pattern, char *entry)
{
    char    *end;

    if (*pattern == '\0' || *pattern == '/')
        return (*entry == '\0');
    if (*pattern == '*')
        return (matches_pattern(pattern + 1, entry) || (matches_pattern(pattern, entry + 1)));
    if (*pattern == *entry)
        return (matches_pattern(pattern + 1, entry + 1));
    return (false);
}

static char  *get_new_pattern(char *basedir, char *entry, char *pattern)
{
    char        *new_pattern;
    uint32_t    size;
    uint32_t    i;

    pattern = ft_strchr(pattern, '/'); //skippo gli * tra / e /
    size = ft_strlen(basedir) + ft_strlen(entry) + ft_strlen(pattern) + 1;
    new_pattern = (char *)malloc_p(sizeof(char) * size);
    ft_strcpy(new_pattern, basedir);
    ft_strcat(new_pattern, entry);
    ft_strcat(new_pattern, pattern);
    return (new_pattern);
}

static char *get_base_dir(char *wildcard_str)
{
    char        *basedir;
    char        *end;
    char        *tmp;
    char        *cwd;
    uint32_t    i;

    tmp = ft_strdup(wildcard_str);
    if (!tmp)
        ft_quit(ERR_MALLOC, "failed to allocate memory");
    end = tmp;
    i = 0;
    while (tmp[i] && tmp[i] != '*')
    {
        if (tmp[i] == '/')
            end += i;
        i++;
    }
    *end = '\0';
    cwd = getcwd(NULL, 0);
    basedir = (char *)malloc_p(sizeof(char) * (ft_strlen(cwd) + ft_strlen(tmp) + 2));
    ft_strcpy(basedir, cwd);
    ft_strcat(basedir, "/");
    ft_strcat(basedir, tmp);
    return (basedir);
}

static char   *get_wildcard_str(char *str, uint32_t *idx)
{
    char    *full_wildcard;
    char    *end;

    while (str[*idx])
    {
        if (str[*idx] == '*')
            break ;
        (*idx)++;
    }
    if (!str[*idx])
        return (NULL);
    while (!is_shell_space(str[*idx]))
        (*idx)--;
    full_wildcard = ft_strdup(&str[*idx]);
    if (!full_wildcard)
        ft_quit(ERR_MALLOC, "failed to allocate memory");
    end = ft_strchr(full_wildcard, ' ');
    if (end)
        *end = '\0';
    return (full_wildcard);
}
