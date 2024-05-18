/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:39:03 by myeow             #+#    #+#             */
/*   Updated: 2024/05/18 15:45:46 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"

/*
 * Must allocate space for null terminator.
 */
char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *) ft_memalloc(size + 1);
	if (!str)
		return (0);
	return (str);
}
