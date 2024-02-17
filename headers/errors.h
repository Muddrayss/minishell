/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <bomboclat@bidol.juis>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:27:05 by craimond          #+#    #+#             */
/*   Updated: 2024/02/17 14:08:30 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ERR_MALLOC     3
# define ERR_FD         4
# define ERR_FORK       5
# define ERR_EXEC       6
# define ERR_ENV        7   //quando non viene trovata una var di ambiente essenziale al corretto funzionamento (tipo PWD ci serve per sapere dove mettere la cartella temp)
# define ERR_SIGSETUP   8  //quando fallisce la funzione signal()
# define ERR_WAIT       9
# define ERR_DIR        10

#endif