/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_methods.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:05:13 by craimond          #+#    #+#             */
/*   Updated: 2024/02/05 11:59:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTECTED_METHODS_H
# define PROTECTED_METHODS_H

void    *malloc_p(size_t size);
void    *calloc_p(size_t count, size_t size);
int     open_p(char *path, int flags, uint16_t permissions);
void    close_p(int fd);
void    pipe_p(int pipefd[2]);
pid_t   fork_p(void);
int     dup_p(int fd);
void    dup2_p(int oldfd, int newfd);
void    wait_p(int *status);
void    waitpid_p(pid_t pid, int *status, int options);
void    signal_p(int signum, void (*handler)(int));
char    *getenv_p( char *name);
void	reset_fd(int *fd);

#endif