/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils_getcwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:27:43 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:13:20 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "msh_perror.h"
#include <string.h>
#include <stdlib.h>

char	*msh_utils_getcwd(char *msg1, char *msg2)
{
	char	*out;

	out = NULL;
	out = getcwd(NULL, 0);
	if (!out)
		msh_perror_exit(msg1, msg2, strerror(errno), EXIT_FAILURE);
	return (out);
}