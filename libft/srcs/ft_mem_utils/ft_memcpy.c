/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:25:03 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:04:34 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void		*dstcpy;
	char		*dst_c;
	const char	*src_c;

	if (n && !dst && !src)
		return (0);
	dstcpy = dst;
	dst_c = dst;
	src_c = src;
	while (n--)
		*dst_c++ = *src_c++;
	return (dstcpy);
}
