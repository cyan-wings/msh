/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:35:23 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 16:17:01 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	msh_perror(char *s1, char *s2, char *msg);

/*
 * Terminates the entire shell with an error message.
 *
 * Usually used when malloc error or file not found.
 */
void	msh_perror_exit(char *s1, char *s2, char *msg, int status)
{
	msh_perror(s1, s2, msg);
	exit(status);
}
