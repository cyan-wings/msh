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

#include "msh_expansion.h"

void	msh_expansion_utils_strappend(char **strptr, int start, int i,
		char **new_strptr)
{
	char	*temp;

	if (start == i)
		return ;
	temp = NULL;
	temp = ft_substr(*strptr, start, i - start);
	if (!temp)
		msh_perror_exit("msh_expansion_utils_strappend", NULL, "malloc fail.", EXIT_FAILURE);
	ft_strappend(new_strptr, temp);
	if (!*new_strptr)
		msh_perror_exit("msh_expansion_utils_strappend", NULL, "malloc fail.", EXIT_FAILURE);
	ft_memdel((void **) &temp);
}
