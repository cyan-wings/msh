/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:35:23 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 17:54:33 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

/*
 * Terminates the entire shell with an error message.
 *
 * Usually used when malloc error.
 *
 * Consider to exit with errno.
 */
void	msh_perror_exit(char *error_msg, int status)
{
	perror(error_msg);
	exit(status);
}
