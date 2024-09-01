/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ft_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:59:36 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 00:20:41 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"

/*
 * Frees any dynamic string array
 */
void	ft_free_ft_split(char **str_array)
{
	int	i;

	i = -1;
	if (str_array)
	{
		while (str_array[++i])
			ft_memdel((void **) &str_array[i]);
		ft_memdel((void **) &str_array);
	}
}
