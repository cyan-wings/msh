/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 22:41:15 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 16:15:09 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string_utils.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		++s1;
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, *(s1 + len - 1)))
		--len;
	return (ft_substr(s1, 0, len));
}
