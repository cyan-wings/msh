/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ft_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:59:36 by myeow             #+#    #+#             */
/*   Updated: 2024/05/18 14:51:39 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"

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
