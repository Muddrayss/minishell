/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:29:45 by craimond          #+#    #+#             */
/*   Updated: 2024/02/22 01:06:49 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char     *get_wildcard_str(char *str, uint32_t *idx);
static char     *get_new_wildcard_str(char *basedir, char *entry, char *wildcard_str);
static char     *get_base_dir(char **wildcard_str);
static void     add_cwd(char **wildcard_str, char *cwd);
static t_list   *parse_wildcard_str(char *wildcard_str);
static bool     matches_pattern(char *pattern, struct dirent *entry, uint32_t idx);
static char     *insert_result(char *original_str, t_list *matching_files, uint32_t idx, char *wildcard_str);

char    *replace_wildcards(char *str)
{
    char        *wildcard_str;
    t_list      *matching_files;
    char        *cwd;
    uint32_t    idx;

    idx = 0;
    wildcard_str = get_wildcard_str(str, &idx);
    cwd = getcwd(NULL, 0);
    if (!cwd)
        ft_quit(ERR_MEM, "Error: failed to get current working directory");
    while (wildcard_str)
    {
        add_cwd(&wildcard_str, cwd);
        matching_files = parse_wildcard_str(wildcard_str);
        lstreverse(&matching_files);
        //TODO sortare la lista con strncmp delle stringhe dopo aver fatto TOLOWER
        str = insert_result(str, matching_files, idx, wildcard_str); //deve fare il free di str
        lstclear(&matching_files, &free);
        idx += ft_strlen(wildcard_str);
        free(wildcard_str);
        wildcard_str = get_wildcard_str(str, &idx);
    }
    return (str);
}

static void add_cwd(char **wildcard_str, char *cwd)
{
    char    *new_wildcard_str;

    new_wildcard_str = (char *)malloc_p(sizeof(char) * (ft_strlen(cwd) + ft_strlen(*wildcard_str) + 2));
    ft_strcpy(new_wildcard_str, cwd);
    ft_strcat(new_wildcard_str, "/");
    ft_strcat(new_wildcard_str, *wildcard_str);
    free(cwd);
    free(*wildcard_str);
    *wildcard_str = new_wildcard_str;
}

//TODO da riscrivere refractandola assulutamente
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
    char            *new_wildcard_str;
    t_list          *matching_files;
    DIR             *dir;
    struct dirent   *entry;
    char            *tmp;

    matching_files = NULL;
    basedir = get_base_dir(&wildcard_str);
    dir = opendir(basedir);
    if (!dir && errno != ENOENT && errno != ENOTDIR)
        ft_quit(ERR_MEM, "Error: failed to access directory");
    while (dir)
    {
        entry = readdir(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.')
            continue ;
        if (matches_pattern(wildcard_str, entry, 0) == true)
        {
            tmp = ft_strdup(entry->d_name);
            if (!tmp)
                return (free(basedir), lstclear(&matching_files, &free), closedir(dir), ft_quit(ERR_MEM, "Error: failed to allocate memory"), NULL);
            new_wildcard_str = get_new_wildcard_str(basedir, wildcard_str, entry->d_name);
            if (!new_wildcard_str)
                lstadd_front(&matching_files, lstnew_p(tmp));
            else
                lstadd_front(&matching_files, parse_wildcard_str(new_wildcard_str));
            free(new_wildcard_str);
        }
    }
    return (free(basedir), closedir(dir), matching_files);
}

static bool matches_pattern(char *pattern, struct dirent *entry, uint32_t idx)
{
    if (entry->d_name[idx] == '\0')
    {
        while (*pattern == '*')
            pattern++;
        return (*pattern == '\0' || (*pattern == '/' && entry->d_type == DT_DIR));
    }
    if (*pattern == '\0' || (*pattern == '/' && entry->d_type == DT_DIR))
        return (false);
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

    while (str[*idx] && str[*idx] != '*')
        (*idx)++;
    if (str[*idx] != '*')
        return (NULL);
    while (*idx > 0 && !is_shell_space(str[*idx]))
        (*idx)--;
    (*idx) += is_shell_space(str[*idx]);
    len = 1;
    while (str[*idx + len] && !is_shell_space(str[*idx + len]))
        len++;
    wildcard_str = (char *)malloc_p(sizeof(char) * (len + 1));
    ft_strlcpy(wildcard_str, &str[*idx], len + 1);
    return (wildcard_str);
}
