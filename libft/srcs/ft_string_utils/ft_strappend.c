/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:10:50 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 17:24:59 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"
#include "ft_mem_utils.h"

/*
 * @params:
 * 		strptr: Pointer to the string. This string must be heap allocated.
 * 				This ptr will hold the buffer and collect the result.
 * 		suffix: The suffix to append. (Stack allocated)
 */
void	ft_strappend(char **strptr, char const *suffix)
{
	char	*new;

	if (!suffix || !strptr)
		return ;
	new = NULL;
	if (!*strptr)
	{
		new = ft_strdup(suffix);
		if (!new)
			return ;
		*strptr = new;
		return ;
	}
	new = ft_strjoin(*strptr, suffix);
	ft_memdel((void **)strptr);
	if (!new)
		return ;
	*strptr = new;
}
