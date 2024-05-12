/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:43:52 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:12:38 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_mem_utils.h"

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dstsize)
		ft_memmove(dst, src, srclen + 1);
	else if (dstsize)
	{
		ft_memmove(dst, src, dstsize - 1);
		dst[--dstsize] = 0;
	}
	return (srclen);
}
