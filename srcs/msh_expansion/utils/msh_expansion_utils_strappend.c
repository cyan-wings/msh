/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_utils_strappend.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:52:58 by myeow             #+#    #+#             */
/*   Updated: 2024/07/11 15:15:29 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_expansion_utils_strappend(char **strptr, int start, int i,
		char **new_strptr)
{
	char	*temp;

	if (start == i)
		return ;
	temp = 0;
	temp = ft_substr(*strptr, start, i - start);
	ft_strappend(new_strptr, temp);
	ft_memdel((void **) &temp);
}
