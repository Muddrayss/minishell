/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:29:45 by craimond          #+#    #+#             */
/*   Updated: 2024/02/19 15:50:02 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char     *get_wildcard_str(char *str, uint32_t *idx);
static char     *get_new_wildcard_str(char *basedir, char *entry, char *wildcard_str);
static char     *get_base_dir(char *wildcard_str);
static t_list   *parse_wildcard_str(char *wildcard_str);
static bool     matches_pattern(char *pattern, char *entry);
static char     *insert_result(char *original_str, t_list *matching_files, uint32_t idx, char *wildcard_str);

char    *replace_wildcards(char *str)
{
    char        *wildcard_str;
    t_list      *matching_files;
    uint32_t    idx;

    wildcard_str = get_wildcard_str(str, &idx);
    while (wildcard_str)
    {
        idx = 0;
        matching_files = parse_wildcard_str(wildcard_str);
        lstreverse(&matching_files);
        lstsort(matching_files, &ft_strcmp);
        str = insert_result(str, matching_files, idx, wildcard_str); //deve fare il free di str
        lstclear(&matching_files, &free);
        free(wildcard_str);
        wildcard_str = get_wildcard_str(str, &idx);
    }
    return (str);
}

static char *insert_result(char *original_str, t_list *matching_files, uint32_t idx, char *wildcard_str)
{
    char        *new_str;
    uint32_t    size;
    uint32_t    filenames_len;
    uint32_t    wildcard_str_len;
    
    wildcard_str_len = ft_strlen(wildcard_str);
    filenames_len = 0;
    while(matching_files)
    {
        filenames_len += ft_strlen(matching_files->content) + 1; //+1 per lo spazio
        matching_files = matching_files->next;
    }
    size = ft_strlen(original_str) - wildcard_str_len + filenames_len + 1;
    new_str = (char *)malloc_p(sizeof(char) * size);
    ft_strlcpy(new_str, original_str, idx + 1);
    while (matching_files)
    {
        ft_strcat(new_str, matching_files->content);
        ft_strcat(new_str, " ");
        matching_files = matching_files->next;
    }
    ft_strcat(new_str, &original_str[idx + wildcard_str_len]);
    return (free(original_str), new_str);
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
    wildcard_str = ft_strchr(wildcard_str, '/') + 1;
    dir = opendir(basedir);
    if (!dir && errno != ENOENT && errno != ENOTDIR)
        ft_quit(ERR_MEM, NULL);
    entry = readdir(dir);
    while (entry)
    {
        if (matches_pattern(wildcard_str, entry->d_name) == true)
        {
            new_wildcard_str = get_new_wildcard_str(basedir, wildcard_str, entry->d_name);
            lstadd_front(&matching_files, parse_wildcard_str(new_wildcard_str));
        }
        entry = readdir(dir);
    }
    closedir(dir);
    return (matching_files);
}

static bool matches_pattern(char *pattern, char *entry)
{
    if (*pattern == '\0' || *pattern == '/')
        return (*entry == '\0');
    if (*pattern == '*')
        return (matches_pattern(pattern + 1, entry) || (matches_pattern(pattern, entry + 1)));
    if (*pattern == *entry)
        return (matches_pattern(pattern + 1, entry + 1));
    return (false);
}

static char  *get_new_wildcard_str(char *basedir, char *entry, char *pattern)
{
    char        *new_pattern;
    uint32_t    size;

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
        ft_quit(ERR_MEM, "failed to allocate memory");
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

static char *get_wildcard_str(char *str, uint32_t *idx)
{
    uint32_t    i;
    uint32_t    len;
    char        *wildcard_str;
    
    i = 0;
    while (str[i] && str[i] != '*')
        i++;
    if (str[i] != '*')
        return (NULL);
    while (i > 0 && !is_shell_space(str[i]))
        i--;
    len = 1;
    while (!is_shell_space(str[i + len]))
        len++;
    wildcard_str = (char *)malloc_p(sizeof(char) * (len + 1));
    ft_strlcpy(wildcard_str, &str[i], len + 1);
    *idx = i;
    return (wildcard_str);
}