/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:34:50 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:35:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
 * This prints an error message but does not terminate the shell.
 * Possible error types:
 * 		(1) Tokenise error.
 * 		(2) Parsing error.
 *
 * May want to include functionality to free up certain stuff.
 */
void	msh_perror(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	return ;
}
