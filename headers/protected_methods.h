/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_methods.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:05:13 by craimond          #+#    #+#             */
/*   Updated: 2024/02/03 11:15:32 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTECTED_METHODS_H
# define PROTECTED_METHODS_H

int     dup_p(int fd);
void    dup2_p(int oldfd, int newfd);
void    close_p(int fd);
void    reset_fd(int *fd);
void    *calloc_p(size_t count, size_t size);
int     open_p(char *path, int flags, int8_t permissions);
void    pipe_p(int pipefd[2]);
void    wait_p(int *status);
void    waitpid_p(pid_t pid, int *status, int options);
void    execve_p(const char *path, char *const argv[], char *const envp[]);
pid_t   fork_p(void);
void    signal_p(int signum, void (*handler)(int));
void    *realloc_p(void *ptr, size_t size);

#endif