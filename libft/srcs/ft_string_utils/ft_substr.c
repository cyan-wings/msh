/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:54:45 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:15:25 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string_utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	if (!s)
		return (0);
	while (start-- && *s)
		++s;
	slen = ft_strlen(s);
	if (len > 2147483646)
		return (0);
	else if (len > slen)
		len = slen;
	str = (char *) malloc(len + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s, len + 1);
	return (str);
}
