/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:45:54 by craimond          #+#    #+#             */
/*   Updated: 2024/02/27 00:55:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char     *get_wildcard_str(char *str, uint32_t *idx);
static char     *get_new_wildcard_str(char *basedir, char *entry, char *wildcard_str);
static char     *get_base_dir(char **wildcard_str);
static void     add_cwd(char **wildcard_str, char *cwd);
static t_list   *parse_wildcard_str(char *wildcard_str, char *cwd);
static bool     matches_pattern(char *pattern, struct dirent *entry, uint32_t idx);
static char     *get_full_entry(char *basedir, char *entry, char *cwd);
static void     sort_result(t_list **matching_files);
static char     *insert_result(char *str, t_list *matching_files, uint32_t idx, uint32_t pattern_len);

char    *replace_wildcards(char *str)
{
    char        *wildcard_str;
    t_list      *matching_files;
    static char *cwd;
    uint32_t    idx;
    uint32_t    pattern_len;

    if (!cwd)
        cwd = getcwd_p(NULL, 0);
    idx = 0;
    wildcard_str = get_wildcard_str(str, &idx);
    while (wildcard_str)
    {
        pattern_len = ft_strlen(wildcard_str);
        add_cwd(&wildcard_str, cwd);
        matching_files = parse_wildcard_str(wildcard_str, cwd);
        sort_result(&matching_files);
        str = insert_result(str, matching_files, idx, pattern_len);
        lstclear(&matching_files, &free);
        idx += pattern_len;
        free(wildcard_str);
        wildcard_str = get_wildcard_str(str, &idx);
    }
    free(cwd);
    cwd = NULL; //perche' e' statica
    return (str);
}

static t_list   *parse_wildcard_str(char *wildcard_str, char *cwd)
{
    char            *basedir;
    char            *new_wildcard_str;
    t_list          *matching_files;
    DIR             *dir;
    struct dirent   *entry;
    char            *full_entry;

    matching_files = NULL;
    basedir = get_base_dir(&wildcard_str);
    dir = opendir_p(basedir);
    while (dir)
    {
        entry = readdir_p(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.' || !matches_pattern(wildcard_str, entry, 0))
            continue ;
        full_entry = get_full_entry(basedir, entry->d_name, cwd);
        new_wildcard_str = get_new_wildcard_str(basedir, wildcard_str, entry->d_name);
        if (!new_wildcard_str)
            lstadd_front(&matching_files, lstnew_p(full_entry));
        else
        {
            free(full_entry);
            lstadd_back(&matching_files, parse_wildcard_str(new_wildcard_str, cwd));
        }
        free(new_wildcard_str);
    }
    return (free(basedir), closedir(dir), matching_files);
}

static char *get_full_entry(char *basedir, char *entry, char *cwd)
{
    char    *full_entry;

    while (*cwd && *basedir == *cwd)
    {
        basedir++;
        cwd++;
    }
    full_entry = (char *)malloc_p(sizeof(char) * (ft_strlen(basedir) + ft_strlen(entry) + 2));
    ft_strcpy(full_entry, basedir);
    ft_strcat(full_entry, "/");
    ft_strcat(full_entry, entry);
    return (full_entry);
}

static bool matches_pattern(char *pattern, struct dirent *entry, uint32_t idx)
{
    if (entry->d_name[idx] == '\0')
    {
        while (*pattern == '*')
            pattern++;
        return (*pattern == '\0' || (*pattern == '/' && entry->d_type == DT_DIR));
    }
    if (*pattern == '*')
        return (matches_pattern(pattern + 1, entry, idx) || matches_pattern(pattern, entry, idx + 1));
    if (*pattern == entry->d_name[idx])
        return (matches_pattern(pattern + 1, entry, idx + 1));
    return (false);
}

static char  *get_new_wildcard_str(char *basedir, char *wildcard_str, char *entry)
{
    char        *new_wildcard_str;
    uint32_t    size;

    wildcard_str = ft_strchr(wildcard_str, '/'); //skippo gli * tra / e /
    if (!wildcard_str)
        return (NULL);
    size = ft_strlen(basedir) + ft_strlen(entry) + ft_strlen(wildcard_str) + 3;
    new_wildcard_str = (char *)calloc_p(size, sizeof(char));
    ft_strcpy(new_wildcard_str, basedir);
    ft_strcat(new_wildcard_str, "/");
    ft_strcat(new_wildcard_str, entry);
    ft_strcat(new_wildcard_str, wildcard_str);
    return (new_wildcard_str);
}

static char *get_base_dir(char **wildcard_str)
{
    char        *basedir;
    uint32_t    end;
    uint32_t    i;

    end = 0;
    i = 0;
    while ((*wildcard_str)[i] && (*wildcard_str)[i] != '*')
    {
        if ((*wildcard_str)[i] == '/')
            end = i;
        i++;
    }
    basedir = (char *)malloc_p(sizeof(char) * (end + 1));
    ft_strlcpy(basedir, *wildcard_str, end + 1);
    *wildcard_str += end + 1;
    return (basedir);
}

static char *get_wildcard_str(char *str, uint32_t *idx)
{
    uint32_t    len;
    char        *wildcard_str;

    while (str[*idx] > 0 && str[*idx] != '*')
        (*idx)++;
    if (str[*idx] != '*')
        return (NULL);
    while (*idx > 0 && !is_shell_space(str[*idx]))
        (*idx)--;
    (*idx) += is_shell_space(str[*idx]);
    len = 1;
    while (str[*idx + len] > 0 && !is_shell_space(str[*idx + len]))
        len++;
    wildcard_str = (char *)malloc_p(sizeof(char) * (len + 1));
    ft_strlcpy(wildcard_str, &str[*idx], len + 1);
    return (wildcard_str);
}

static void sort_result(t_list **matching_files)
{
    t_list  *node;
    t_list  *next;
    char    *tmp;

    node = *matching_files;
    while (node)
    {
        next = node->next;
        while (next)
        {
            if (ft_strcmp_lower(node->content, next->content) > 0)
            {
                tmp = node->content;
                node->content = next->content;
                next->content = tmp;
            }
            next = next->next;
        }
        node = node->next;
    }
}

static void add_cwd(char **wildcard_str, char *cwd)
{
    char    *new_wildcard_str;

    new_wildcard_str = (char *)malloc_p(sizeof(char) * (ft_strlen(cwd) + ft_strlen(*wildcard_str) + 2));
    ft_strcpy(new_wildcard_str, cwd);
    ft_strcat(new_wildcard_str, "/");
    ft_strcat(new_wildcard_str, *wildcard_str);
    free(*wildcard_str);
    *wildcard_str = new_wildcard_str;
}

static char *insert_result(char *str, t_list *matching_files, uint32_t idx, uint32_t pattern_len)
{
    char        *new_str;
    t_list      *node;
    uint32_t    size;
    uint32_t    filenames_len;

    if (!matching_files)
        return (str);
    node = matching_files;
    filenames_len = 0;
    while(node)
    {
        filenames_len += ft_strlen(node->content) + 1; //+1 per lo spazio
        node = node->next;
    }
    size = ft_strlen(str) - pattern_len + filenames_len + 1;
    new_str = (char *)malloc_p(sizeof(char) * size);
    ft_strlcpy(new_str, str, idx + 1);
    node = matching_files;
    while (node)
    {
        ft_strcat(new_str, node->content);
        ft_strcat(new_str, " ");
        node = node->next;
    }
    ft_strcat(new_str, &str[idx + pattern_len]);
    return (free(str), new_str);
}