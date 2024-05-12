/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ft_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:59:36 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:14:14 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_ft_split(char **str_array)
{
	int	i;

	i = -1;
	if (str_array)
	{
		while (str_array[++i])
		{
			free(str_array[i]);
			str_array[i] = 0;
		}
		free(str_array);
		str_array = 0;
	}
}
