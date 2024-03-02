/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:04:13 by craimond          #+#    #+#             */
/*   Updated: 2024/03/03 00:03:41 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# define S_INTERACTIVE  0
# define S_HEREDOC      1
# define S_COMMAND      2
# define S_SILENT       3

void    set_signals(uint8_t mode, bool is_main);

#endif
