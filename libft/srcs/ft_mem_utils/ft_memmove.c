/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:06:01 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:04:36 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_mem_utils.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*dst_c;
	const char	*src_c;

	dst_c = dst;
	src_c = src;
	if (!n || dst == src)
		return (dst);
	if (dst > src && dst < src + n)
	{
		while (n--)
			dst_c[n] = src_c[n];
		return (dst);
	}
	ft_memcpy(dst, src, n);
	return (dst);
}
