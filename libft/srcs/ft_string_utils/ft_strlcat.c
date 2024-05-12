/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:11:38 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:14:22 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	if (!dst && !dstsize)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	i = 0;
	while (src[i] && (dstlen + i + 1) < dstsize)
	{
		dst[dstlen + i] = src[i];
		++i;
	}
	dst[dstlen + i] = 0;
	return (srclen + dstlen);
}
