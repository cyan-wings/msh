/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_utils_strappend.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:52:58 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 19:40:51 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"
#include "ft_mem_utils.h"

void	msh_expansion_utils_strappend(char **strptr, int start, int i,
		char **new_strptr)
{
	char	*temp;

	if (start == i)
		return ;
	temp = NULL;
	temp = ft_substr(*strptr, start, i - start);
	ft_strappend(new_strptr, temp);
	ft_memdel((void **) &temp);
}
