/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:29:45 by craimond          #+#    #+#             */
/*   Updated: 2024/02/20 20:13:16 by craimond         ###   ########.fr       */
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

    idx = 0;
    wildcard_str = get_wildcard_str(str, &idx);
    while (wildcard_str)
    {
        matching_files = parse_wildcard_str(wildcard_str);
        lstreverse(&matching_files);
        lstsort(matching_files, &ft_strcmp);
        str = insert_result(str, matching_files, idx, wildcard_str); //deve fare il free di str
        lstclear(&matching_files, &free);
        idx += ft_strlen(wildcard_str);
        free(wildcard_str);
        wildcard_str = get_wildcard_str(str, &idx);
    }
    return (str);
}

static char *insert_result(char *original_str, t_list *matching_files, uint32_t idx, char *wildcard_str)
{
    char        *new_str;
    t_list      *node;
    uint32_t    size;
    uint32_t    filenames_len;
    uint32_t    wildcard_str_len;
    
    if (!matching_files)
    {
        new_str = ft_strdup(original_str);
        if (!new_str)
            ft_quit(ERR_MEM, "Error: failed to allocate memory");
        return (free(original_str), new_str);
    }
    node = matching_files;
    wildcard_str_len = ft_strlen(wildcard_str);
    filenames_len = 0;
    while(node)
    {
        filenames_len += ft_strlen(node->content) + 1; //+1 per lo spazio
        node = node->next;
    }
    size = ft_strlen(original_str) - wildcard_str_len + filenames_len + 1;
    new_str = (char *)malloc_p(sizeof(char) * size);
    ft_strlcpy(new_str, original_str, idx + 1);
    node = matching_files;
    while (node)
    {
        ft_strcat(new_str, node->content);
        ft_strcat(new_str, " ");
        node = node->next;
    }
    ft_strcat(new_str, &original_str[idx + wildcard_str_len]);
    return (free(original_str), new_str);
}

static t_list   *parse_wildcard_str(char *wildcard_str)
{
    char            *basedir;
    char            *tmp;
    char            *new_wildcard_str;
    t_list          *matching_files;
    DIR             *dir;
    struct dirent   *entry;

    if (!wildcard_str)
        return (NULL);
    matching_files = NULL;
    basedir = get_base_dir(wildcard_str);
    tmp = ft_strchr(wildcard_str, '/');
    if (tmp)
        wildcard_str = tmp + 1;        
    dir = opendir(basedir);
    if (!dir && errno != ENOENT && errno != ENOTDIR)
        ft_quit(ERR_MEM, "Error: failed to allocate memory");
    while (true)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (ft_strcmp(entry->d_name, ".") == 0 ||  ft_strcmp(entry->d_name, "..") == 0)
            continue ;
        if (matches_pattern(wildcard_str, entry->d_name) == true)
        {
            new_wildcard_str = get_new_wildcard_str(basedir, wildcard_str, entry->d_name);
            tmp = ft_strdup(entry->d_name);
            if (!tmp)
                ft_quit(ERR_MEM, "Error: failed to allocate memory");
            if (!new_wildcard_str)
                lstadd_front(&matching_files, lstnew_p(tmp));
            else
                lstadd_front(&matching_files, parse_wildcard_str(new_wildcard_str));
        }
    }
    return (free(basedir), closedir(dir), matching_files);
}

static bool matches_pattern(char *pattern, char *entry)
{
    if (*entry == '\0')
    {
        while (*pattern == '*')
            pattern++;
        return (*pattern == '\0');
    }
    if (*pattern == '\0')
        return (false);
    if (*pattern == '*')
        return (matches_pattern(pattern + 1, entry) || matches_pattern(pattern, entry + 1));
    if (*pattern == *entry)
        return (matches_pattern(pattern + 1, entry + 1));
    return (false);
}

static char  *get_new_wildcard_str(char *basedir, char *entry, char *pattern)
{
    char        *new_pattern;
    uint32_t    size;

    pattern = ft_strchr(pattern, '/'); //skippo gli * tra / e /
    if (!pattern)
        return (NULL);
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
        ft_quit(ERR_MEM, "Error: failed to allocate memory");
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
    if (!cwd)
        ft_quit(ERR_MEM, "Error: failed to allocate memory");
    basedir = (char *)malloc_p(sizeof(char) * (ft_strlen(cwd) + ft_strlen(tmp) + 2));
    ft_strcpy(basedir, cwd);
    ft_strcat(basedir, "/");
    ft_strcat(basedir, tmp);
    return (free(tmp), free(cwd), basedir);
}

static char *get_wildcard_str(char *str, uint32_t *idx)
{
    uint32_t    len;
    char        *wildcard_str;

    while (str[*idx] && str[*idx] != '*')
        (*idx)++;
    if (str[*idx] != '*')
        return (NULL);
    while (*idx > 0 && !is_shell_space(str[*idx]))
        (*idx)--;
    len = 0;
    (*idx)++;
    while (str[*idx + len] && !is_shell_space(str[*idx + len]))
        len++;
    wildcard_str = (char *)malloc_p(sizeof(char) * (len + 1));
    ft_strlcpy(wildcard_str, &str[*idx], len + 1);
    return (wildcard_str);
}
