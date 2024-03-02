/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_methods.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:05:13 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 00:34:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTECTED_METHODS_H
# define PROTECTED_METHODS_H

void            *malloc_p(size_t size);
void            *calloc_p(size_t nmemb, size_t size);
uint16_t        open_p(char *path, int32_t flags, uint16_t permissions);
void            close_p(int16_t fd);
DIR             *opendir_p(char *path);
struct dirent   *readdir_p(DIR *dir);
char            *getcwd_p(char *buf, size_t size);
int32_t         chdir_p(char *path);
void            pipe_p(int16_t pipefd[2]);
pid_t           fork_p(void);
uint16_t        dup_p(uint16_t fd);
void            dup2_p(uint16_t oldfd, uint16_t newfd);
void            wait_p(int32_t *status);
void            waitpid_p(pid_t pid, int32_t *status, int32_t options);
void            signal_p(int32_t signo, __sighandler_t handler);
void            sigaction_p(int32_t signo, struct sigaction *act, struct sigaction *oldact);
void	        reset_fd(int16_t *fd);

#endif