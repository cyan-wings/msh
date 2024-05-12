/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:26:39 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:51:18 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needlelen;

	if (!haystack && !len)
		return (0);
	needlelen = ft_strlen(needle);
	if (!needlelen)
		return ((char *) haystack);
	while (*haystack && len)
	{
		if (*needle == *haystack)
		{
			i = 1;
			while ((len - i) && needle[i] \
					&& needle[i] == haystack[i])
				++i;
			if (i == needlelen)
				return ((char *) haystack);
		}
		++haystack;
		--len;
	}
	return (0);
}
