/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:39:03 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:50:59 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *) ft_memalloc(size);
	if (!str)
		return (0);
	return (str);
}
