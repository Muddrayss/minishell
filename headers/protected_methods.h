/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_methods.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:05:13 by craimond          #+#    #+#             */
/*   Updated: 2024/03/05 16:52:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTECTED_METHODS_H
# define PROTECTED_METHODS_H

void			*malloc_p(const size_t size);
void			*calloc_p(const size_t count, const size_t size);
int32_t			chdir_p(const char *const path);
DIR				*opendir_p(const char *const name);
struct dirent	*readdir_p(const DIR *const dir);
char			*getcwd_p(const char *const buf, const size_t size);
uint16_t		dup_p(const uint16_t fd);
void			dup2_p(const uint16_t oldfd, const uint16_t newfd);
uint16_t		open_p(const char *const path, const int32_t flags, const uint16_t mode);
void			close_p(const int16_t fd);
void			reset_fd(int16_t *const fd);
void			pipe_p(int16_t *const fds);
pid_t			fork_p(void);
void			signal_p(const int32_t signo, const __sighandler_t handler);
void			sigaction_p(const int32_t signo, const struct sigaction *act, struct sigaction *oldact);
void			wait_p(int32_t *const status);
void			waitpid_p(const pid_t pid, int32_t *const status, const int32_t options);

#endif