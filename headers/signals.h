/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:04:13 by craimond          #+#    #+#             */
/*   Updated: 2024/02/01 16:22:03 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void    set_sighandler(void *handle_sigint, void *handle_sigquit);
void    display_signal(int signo);
void    hide_signal(int signo);
void    hide_quit_signal(int signo);

#endif
