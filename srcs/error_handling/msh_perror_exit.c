/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:35:23 by myeow             #+#    #+#             */
/*   Updated: 2024/08/27 15:22:38 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
 * Terminates the entire shell with an error message.
 *
 * Usually used when malloc error.
 */
void	msh_perror_exit(char *error_msg, int status)
{
	perror(error_msg);
	exit(status);
}
