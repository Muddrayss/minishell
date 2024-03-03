/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcards.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 01:45:54 by craimond          #+#    #+#             */
/*   Updated: 2024/03/04 00:03:48 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_list   *parse_pattern(const char *const pattern, const char *const cwd, const bool is_root);
static char     *get_full_entry(const char *basedir, const char *const entry, const char *cwd, const bool is_root);
static bool     matches_pattern(const char *pattern, const struct dirent *const entry, const uint16_t idx);
static char     *get_new_pattern(const char *const basedir, const char *pattern, const char *const entry);
static char     *get_base_dir(const char **const pattern, bool *const is_root);
static char     *get_pattern(const char *const str, uint16_t *const i, uint16_t *const len);
static t_list   *sort_result(t_list *matching_files);
static char     *add_cwd(const char *pattern, const char *const cwd);
static char     *insert_result(const char *const str, const t_list *const matching_files, const uint16_t idx, const uint16_t pattern_len);


//TODO non funziona echo ./*/*
void    replace_wildcards(char **const str)
{
    t_list              *matching_files;
    char                *pattern;
    const char *const   cwd = getcwd_p(NULL, 0);
    uint16_t            idx;
    uint16_t            len;

    idx = 0;
    pattern = get_pattern(*str, &idx, &len);
    while (pattern)
    {
        pattern = add_cwd(pattern, cwd);
        matching_files = parse_pattern(pattern, cwd, false);
        matching_files = sort_result(matching_files);
        *str = insert_result(*str, matching_files, idx, len);
        lstclear(&matching_files, (void *const)&free);
        idx += len;
        free_and_null((void **)&pattern);
        pattern = get_pattern(*str, &idx, &len);
    }
    free_and_null((void **)&cwd);
}

static t_list   *parse_pattern(const char *pattern, const char *const cwd, const bool is_root)
{
    struct dirent       *entry;
    t_list              *matching_files;
    char                *new_pattern;
    char                *full_entry;
    const char *const   basedir = get_base_dir(&pattern, (bool *)&is_root);
    const DIR  *const   dir = opendir_p(basedir);

    matching_files = NULL;
    while (dir)
    {
        entry = readdir_p(dir);
        if (!entry)
            break ;
        if (entry->d_name[0] == '.' || !matches_pattern(pattern, entry, 0))
            continue ;
        full_entry = get_full_entry(basedir, entry->d_name, cwd, is_root);
        new_pattern = get_new_pattern(basedir, pattern, entry->d_name);
        if (!new_pattern)
            lstadd_front(&matching_files, lstnew_p(full_entry));
        else
        {
            free_and_null((void **)&full_entry);
            lstadd_back(&matching_files, parse_pattern(new_pattern, cwd, is_root));
        }
        free_and_null((void **)&new_pattern);
    }
    return (free_and_null((void **)&basedir), closedir((DIR *)dir), matching_files);
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

static char  *get_new_pattern(const char *const basedir, const char *pattern, const char *const entry)
{
    char        *new_pattern;
    uint16_t    size;

    pattern = ft_strchr(pattern, '/'); //skippo gli * tra / e /
    if (!pattern)
        return (NULL);
    size = ft_strlen(basedir) + ft_strlen(entry) + ft_strlen(pattern) + 3;
    new_pattern = (char *)calloc_p(size, sizeof(char));
    ft_strcpy(new_pattern, basedir);
    ft_strcat(new_pattern, "/");
    ft_strcat(new_pattern, entry);
    ft_strcat(new_pattern, pattern);
    return (new_pattern);
}

static char *get_base_dir(const char **const pattern, bool *const is_root)
{
    char        *basedir;
    uint16_t    end;
    uint16_t    i;

    end = 0;
    i = 0;
    while ((*pattern)[i] && (*pattern)[i] != '*')
    {
        if ((*pattern)[i] == '/')
            end = i;
        i++;
    }
    basedir = (char *)malloc_p(sizeof(char) * (end + 1));
    ft_strlcpy(basedir, *pattern, end + 1);
    *pattern += end + 1;
    if (!basedir[0])
    {
        *is_root = true;
        return (free_and_null((void **)&basedir), strdup_p("/"));
    }
    return (basedir);
}

static char *get_pattern(const char *const str, uint16_t *const i, uint16_t *const len)
{
    char        *pattern;
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
    pattern = (char *)malloc_p(sizeof(char) * (*len + 1));
    ft_strlcpy(pattern, &str[*i], *len + 1);
    return (clear_quotes(&pattern), pattern);
}

static t_list *sort_result(t_list *matching_files)
{
    const t_list *const head = matching_files;
    t_list              *next;
    char                *tmp;

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
    return ((t_list *)head);
}

static char *add_cwd(const char *pattern, const char *const cwd)
{
    char    *new_pattern;

    if (pattern[0] == '/')
    {
        new_pattern = strdup_p(pattern);
        return (free_and_null((void **)&pattern), new_pattern);
    }
    new_pattern = (char *)malloc_p(sizeof(char) * (ft_strlen(cwd) + ft_strlen(pattern) + 2));
    ft_strcpy(new_pattern, cwd);
    ft_strcat(new_pattern, "/");
    ft_strcat(new_pattern, pattern);
    return (free_and_null((void **)&pattern), new_pattern);
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