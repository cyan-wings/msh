/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:34:50 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 16:16:36 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print_utils.h"
#include <unistd.h>
#include "msh_perror.h"

/*
 * This prints an error message but does not terminate the shell.
 * Possible examples of error types:
 * 		(1) Tokenise error.
 * 		(2) Parsing error.
 * 		(3) Open or close dir error during wildcards expansion.
 */
void	msh_perror(char *s1, char *s2, char *msg)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	if (s1)
		ft_putstr_fd(s1, STDERR_FILENO);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(s2, STDERR_FILENO);
	}
	if (msg)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
}
