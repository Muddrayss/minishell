/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_methods.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:01:04 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 13:54:42 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int    dup_p(int fd)
{
    int    newfd;

    newfd = dup(fd);
    if (newfd == -1)
        ft_quit(8, NULL);
    return (newfd);
}

void    dup2_p(int oldfd, int newfd)
{
    if (dup2(oldfd, newfd) == -1)
        ft_quit(8, NULL);
}

void    close_p(int fd)
{
    if (close(fd) == -1)
        ft_quit(8, NULL);
}

void    reset_fd(int *fd)
{
    if (*fd != -1)
        close_p(*fd);
    *fd = -1;
}

int    open_p(char *path, int flags, int8_t permissions)
{
    int    fd;

    fd = open(path, flags, permissions);
    if (fd == -1)
        ft_quit(8, NULL);
    return (fd);
}

void    pipe_p(int pipefd[2])
{
    if (pipe(pipefd) == -1)
        ft_quit(8, NULL);
}

void    wait_p(int *status)
{
    if (wait(status) == -1)
        ft_quit(8, NULL);
}

void    waitpid_p(pid_t pid, int *status, int options)
{
    if (waitpid(pid, status, options) == -1)
        ft_quit(8, NULL);
}

void    execve_p(const char *path, char *const argv[], char *const envp[])
{
    if (execve(path, argv, envp) == -1)
        ft_quit(8, NULL);
}

pid_t    fork_p(void)
{
    pid_t    pid;

    pid = fork();
    if (pid == -1)
        ft_quit(8, NULL);
    return (pid);
}

void    signal_p(int signum, void (*handler)(int))
{
    if (signal(signum, handler) == SIG_ERR)
        ft_quit(8, NULL);
}

void    *calloc_p(size_t count, size_t size)
{
    void    *ptr;

    ptr = calloc(count, size);
    if (!ptr)
        ft_quit(14, NULL);
    return (ptr);
}

void    *malloc_p(size_t size)
{
    void    *ptr;

    ptr = malloc(size);
    if (!ptr)
        ft_quit(14, NULL);
    return (ptr);
}

void    *realloc_p(void *ptr, size_t nmemb, int8_t size)
{
    void    *new_ptr;

    free(ptr);
    ptr = malloc_p(nmemb * size);
    return (ptr);
}