/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils_strrpad.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:53:31 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 16:10:59 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"
#include "ft_mem_utils.h"

/*
 * Removes the string's the first and last character which is
 * parameterised as padding.
 * 
 */
void	msh_utils_strrpad(char **strptr, char padding)
{
	int		len;
	char	*buf;

	len = ft_strlen(*strptr);
	if ((*strptr)[0] == padding && (*strptr)[len - 1] == padding)
	{
		buf = NULL;
		buf = ft_memalloc(len - 2 + 1);
		ft_strlcpy(buf, *strptr + 1, len - 1);
		ft_memdel((void **)strptr);
		*strptr = buf;
	}
}
