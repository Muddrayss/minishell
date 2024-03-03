/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:45:54 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 18:35:47 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_list   *parse_wildcard_str(const char *const wildcard_str, const char *const cwd, const bool is_root);
static char     *get_full_entry(const char *basedir, const char *const entry, const char *cwd, const bool is_root);
static bool     matches_pattern(const char *pattern, const struct dirent *const entry, const uint16_t idx);
static char     *get_new_wildcard_str(const char *const basedir, const char *wildcard_str, const char *const entry);
static char     *get_base_dir(const char **const wildcard_str, bool *const is_root);
static char     *get_wildcard_str(const char *const str, uint16_t *const i, uint16_t *const len);
static t_list   *sort_result(t_list *matching_files);
static char     *add_cwd(const char *wildcard_str, const char *const cwd);
static char     *insert_result(const char *const str, const t_list *const matching_files, const uint16_t idx, const uint16_t pattern_len);

void    replace_wildcards(char **const str)
{
    t_list      *matching_files;
    char        *wildcard_str;
    char        *cwd;
    uint16_t    idx;
    uint16_t    len;

    cwd = getcwd_p(NULL, 0);
    idx = 0;
    wildcard_str = get_wildcard_str(*str, &idx, &len);
    while (wildcard_str)
    {
        wildcard_str = add_cwd(wildcard_str, cwd);
        matching_files = parse_wildcard_str(wildcard_str, cwd, false);
        matching_files = sort_result(matching_files);
        *str = insert_result(*str, matching_files, idx, len);
        lstclear(&matching_files, (void *const)&free);
        idx += len;
        free_and_null((void **)&wildcard_str);
        wildcard_str = get_wildcard_str(*str, &idx, &len);
    }
    free_and_null((void **)&cwd);
}

static t_list   *parse_wildcard_str(const char *wildcard_str, const char *const cwd, const bool is_root)
{
    DIR             *dir;
    struct dirent   *entry;
    t_list          *matching_files;
    char            *basedir;
    char            *new_wildcard_str;
    char            *full_entry;

    matching_files = NULL;
    basedir = get_base_dir(&wildcard_str, (bool *)&is_root);
    dir = opendir_p(basedir);
    while (dir)
    {
        entry = readdir_p(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.' || !matches_pattern(wildcard_str, entry, 0))
            continue ;
        full_entry = get_full_entry(basedir, entry->d_name, cwd, is_root);
        new_wildcard_str = get_new_wildcard_str(basedir, wildcard_str, entry->d_name);
        if (!new_wildcard_str)
            lstadd_front(&matching_files, lstnew_p(full_entry));
        else
        {
            free_and_null((void **)&full_entry);
            lstadd_back(&matching_files, parse_wildcard_str(new_wildcard_str, cwd, is_root));
        }
        free_and_null((void **)&new_wildcard_str);
    }
    return (free_and_null((void **)&basedir), closedir(dir), matching_files);
}

static char *get_full_entry(const char *basedir, const char *const entry, const char *cwd, const bool is_root)
{
    char    *full_entry;

    while (*cwd && *basedir == *cwd)
    {
        basedir++;
        cwd++;
    }
    if (*basedir == '/')
        basedir++;
    full_entry = (char *)calloc_p(ft_strlen(basedir) + ft_strlen(entry) + 2 + is_root, sizeof(char));
    if (is_root)
        ft_strcat(full_entry, "/");
    if (*basedir)
    {
        ft_strcat(full_entry, basedir);
        ft_strcat(full_entry, "/");
    }
    ft_strcat(full_entry, entry);
    return (full_entry);
}

static bool matches_pattern(const char *pattern, const struct dirent *const entry, const uint16_t idx)
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

static char  *get_new_wildcard_str(const char *const basedir, const char *wildcard_str, const char *const entry)
{
    char        *new_wildcard_str;
    uint16_t    size;

    wildcard_str = ft_strchr(wildcard_str, '/'); //skippo gli * tra / e /
    if (!wildcard_str)
        return (NULL);
    size = ft_strlen(basedir) + ft_strlen(entry) + ft_strlen(wildcard_str) + 3;
    new_wildcard_str = (char *)calloc_p(size, sizeof(char));
    if (basedir[0] != '/')
        ft_strcpy(new_wildcard_str, basedir);
    ft_strcat(new_wildcard_str, "/");
    ft_strcat(new_wildcard_str, entry);
    ft_strcat(new_wildcard_str, wildcard_str);
    return (new_wildcard_str);
}

static char *get_base_dir(const char **const wildcard_str, bool *const is_root)
{
    char        *basedir;
    uint16_t    end;
    uint16_t    i;

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
    if (!basedir[0])
    {
        *is_root = true;
        return (free_and_null((void **)&basedir), strdup_p("/"));
    }
    return (basedir);
}

static char *get_wildcard_str(const char *const str, uint16_t *const i, uint16_t *const len)
{
    char        *wildcard_str;
    char        master_quote;

    if (!str)
        return (NULL);
    master_quote = '\0';
    while (str[*i])
    {
        if (!master_quote && (is_quote(str[*i])))
            master_quote = str[*i];
        else if (master_quote && str[*i] == master_quote)
            master_quote = '\0';
        if (!master_quote && str[*i] == '*')
            break ;
        (*i)++;
    }
    if (str[*i] != '*')
        return (NULL);
    while (*i > 0 && !is_shell_space(str[*i]))
        (*i)--;
    *i += is_shell_space(str[*i]);
    *len = 1;
    while (str[*i + *len] && !is_shell_space(str[*i + *len]) && !is_quote(str[*i + *len]))
        (*len)++;
    wildcard_str = (char *)malloc_p(sizeof(char) * (*len + 1));
    ft_strlcpy(wildcard_str, &str[*i], *len + 1);
    return (clear_quotes(&wildcard_str), wildcard_str);
}

static t_list *sort_result(t_list *matching_files)
{
    t_list  *head;
    t_list  *next;
    char    *tmp;

    head = matching_files;
    while (matching_files)
    {
        next = matching_files->next;
        while (next)
        {
            if (ft_strcmp_lower(matching_files->content, next->content) > 0)
            {
                tmp = matching_files->content;
                matching_files->content = next->content;
                next->content = tmp;
            }
            next = next->next;
        }
        matching_files = matching_files->next;
    }
    return (head);
}

static char *add_cwd(const char *wildcard_str, const char *const cwd)
{
    char    *new_wildcard_str;

    if (wildcard_str[0] == '/')
    {
        new_wildcard_str = strdup_p(wildcard_str);
        return (free_and_null((void **)&wildcard_str), new_wildcard_str);
    }
    new_wildcard_str = (char *)malloc_p(sizeof(char) * (ft_strlen(cwd) + ft_strlen(wildcard_str) + 2));
    ft_strcpy(new_wildcard_str, cwd);
    ft_strcat(new_wildcard_str, "/");
    ft_strcat(new_wildcard_str, wildcard_str);
    return (free_and_null((void **)&wildcard_str), new_wildcard_str);
}

static char *insert_result(const char *const str, const t_list *const matching_files, const uint16_t idx, const uint16_t pattern_len)
{
    t_list      *node;
    char        *new_str;
    uint16_t    size;
    uint16_t    filenames_len;

    if (!matching_files)
        return ((char *)str);
    node = (t_list *)matching_files;
    filenames_len = 0;
    while(node)
    {
        filenames_len += ft_strlen(node->content) + 1; //+1 per lo spazio
        node = node->next;
    }
    size = ft_strlen(str) - pattern_len + filenames_len + 1;
    new_str = (char *)malloc_p(sizeof(char) * size);
    ft_strlcpy(new_str, str, idx + 1);
    node = (t_list *)matching_files;
    while (node)
    {
        ft_strcat(new_str, node->content);
        ft_strcat(new_str, " ");
        node = node->next;
    }
    ft_strcat(new_str, &str[idx + pattern_len]);
    return (free_and_null((void **)&str), new_str);
}