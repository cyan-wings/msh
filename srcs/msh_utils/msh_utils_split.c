/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:27:43 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:13:39 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"
#include "msh_perror.h"
#include <stdlib.h>

char	**msh_utils_split(char *str, char c, char *msg1, char *msg2)
{
	char	**out;

	out = NULL;
	out = ft_split(str, c);
	if (!out)
		msh_perror_exit(msg1, msg2, "malloc fail.", EXIT_FAILURE);
	return (out);
}
