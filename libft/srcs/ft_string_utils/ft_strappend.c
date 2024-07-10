/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:10:50 by myeow             #+#    #+#             */
/*   Updated: 2024/07/10 22:13:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"
#include "ft_mem_utils.h"
#include <stdio.h>

void	ft_strappend(char **ptr, char const *add)
{
	char *new;

	if (!add || !ptr)
		return ;
	if (!*ptr)
	{
		new = ft_strdup(add);
		*ptr = new;
		return ;
	}
	new = ft_strjoin(*ptr, add);
	ft_memdel((void **) ptr);
	*ptr = new;
}
