/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:26:25 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:04:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"

void	*ft_memalloc(size_t size)
{
	void	*ptr;

	ptr = ft_calloc(size, 1);
	if (!ptr)
		return (0);
	return (ptr);
}
