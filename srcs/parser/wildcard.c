/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:22:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/16 18:25:02 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char     *get_wildcard_str(char *str, uint32_t *idx);
static char     *get_new_wildcard_str(char *basedir, char *entry, char *wildcard_str);
static char     *get_base_dir(char *wildcard_str);
static t_list   *parse_wildcard_str(char *wildcard_str);
static bool     matches_pattern(char *wildcard_str, char *entry);


void    replace_wildcards(char *str)
{
    char        *wildcard_str;
    t_list      *matching_files;
    uint32_t    idx;

    while (true)
    {
        wildcard_str = get_wildcard_str(str, &idx);
        if (!wildcard_str)
            break ;
        matching_files = parse_wildcard_str(wildcard_str);
        ft_lstreverse(&matching_files);
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
    struct dirent   *entry;

    matching_files = NULL;
    basedir = get_base_dir(wildcard_str);
    wildcard_str = ft_strrchr(wildcard_str, '/') + 1;
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

static bool matches_pattern(char *wildcard_str, char *entry)
{
    char    *end;

    end = ft_strchr(wildcard_str, '/');
    if (end)
        *end = '\0';
    while (*wildcard_str && *entry)
    {
        if (*wildcard_str == '*')
        {
            
        }
        wildcard_str++;
        entry++;
    }
    if (end)
        *end = '/';
}

static char  *get_new_wildcard_str(char *basedir, char *entry, char *wildcard_str)
{
    char        *new_wildcard_str;
    uint32_t    size;
    uint32_t    i;

    wildcard_str = ft_strrchr(wildcard_str, '/'); //skippo gli * tra / e /
    size = ft_strlen(basedir) + ft_strlen(entry) + ft_strlen(wildcard_str) + 1;
    new_wildcard_str = (char *)malloc_p(sizeof(char) * size);
    ft_strcpy(new_wildcard_str, basedir);
    ft_strcat(new_wildcard_str, entry);
    ft_strcat(new_wildcard_str, wildcard_str);
    return (new_wildcard_str);
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

    while (*str)
    {
        if (*str == '*')
            break ;
        str++;
    }
    if (!*str)
        return (NULL);
    while (!is_shell_space(*str))
        str--;
    *idx = str;
    full_wildcard = ft_strdup(str);
    if (!full_wildcard)
        ft_quit(ERR_MALLOC, "failed to allocate memory");
    end = ft_strchr(full_wildcard, ' ');
    if (end)
        *end = '\0';
    return (full_wildcard);
}
