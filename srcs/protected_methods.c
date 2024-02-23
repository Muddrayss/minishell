/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_methods.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:01:04 by craimond          #+#    #+#             */
/*   Updated: 2024/02/23 13:53:50 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static bool is_bad_errno(uint8_t value);

void    *malloc_p(size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
        ft_quit(ERR_MEM, "Error: failed to allocate memory");
    return (ptr);
}

void    *calloc_p(size_t nmemb, size_t size)
{
    void    *ptr;

    ptr = calloc(nmemb, size);
    if (!ptr)
        ft_quit(ERR_MEM, "Error: failed to allocate memory");
    return (ptr);
}

int    open_p(char *path, int flags, uint16_t permissions)
{
    int    fd;

    fd = open(path, flags, permissions);
    if (fd == -1)
        ft_quit(ERR_FD, NULL);
    return (fd);
}

void    close_p(int fd)
{
    if (close(fd) == -1)
        ft_quit(ERR_FD, NULL);
}

DIR *opendir_p(char *path)
{
    DIR    *dir;

    dir = opendir(path);
    if (!dir && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (dir);
}

struct dirent   *readdir_p(DIR *dir)
{
    struct dirent    *entry;

    entry = readdir(dir);
    if (!entry && is_bad_errno(errno))
        ft_quit(ERR_MEM, NULL);
    return (entry);
}

void    pipe_p(int fds[2])
{
    if (pipe(fds) == -1)
        ft_quit(ERR_FD, NULL);
}

pid_t    fork_p(void)
{
    pid_t    pid;

    pid = fork();
    if (pid == -1)
        ft_quit(ERR_FORK, NULL);
    return (pid);
}

int    dup_p(int fd)
{
    int    newfd;

    newfd = dup(fd);
    if (newfd == -1)
        ft_quit(ERR_FD, NULL);
    return (newfd);
}

void    dup2_p(int oldfd, int newfd)
{
    if (dup2(oldfd, newfd) == -1)
        ft_quit(ERR_FD, NULL);
}

void    wait_p(int *status)
{
    if (wait(status) == -1)
        ft_quit(ERR_WAIT, NULL);
}

void    waitpid_p(pid_t pid, int *status, int options)
{
    if (waitpid(pid, status, options) == -1)
        ft_quit(ERR_WAIT, NULL);
}

void    signal_p(int signum, void (*handler)(int))
{
    if (signal(signum, handler) == SIG_ERR)
        ft_quit(ERR_SIGSETUP, NULL);
}

void    sigaction_p(int signum, struct sigaction *act, struct sigaction *oldact)
{
    if (sigaction(signum, act, oldact) == -1)
        ft_quit(ERR_SIGSETUP, NULL);
}

void    reset_fd(int *fd)
{
    if (*fd >= 0)
        close_p(*fd);
    *fd = -42;
}

static bool is_bad_errno(uint8_t value)
{
    static uint8_t   bad_errnos[256];

    if (bad_errnos[ENOMEM] == false) //solo la prima volta
    {
        bad_errnos[ENOMEM] = true;
        bad_errnos[EFAULT] = true;
        bad_errnos[EMFILE] = true;
        bad_errnos[ENFILE] = true;
        bad_errnos[EIO] = true;
        bad_errnos[ENOSPC] = true;
        bad_errnos[EPIPE] = true;
        bad_errnos[EAGAIN] = true;
        bad_errnos[ELOOP] = true;
    }
    return (bad_errnos[value]);
}