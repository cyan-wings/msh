/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 19:51:44 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 20:19:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"

char	*ft_strtok_r(char *str, const char *sep, char **last)
{
	char	*start;

	if (!sep || !last)
		return (0);
	if (!str)
		str = *last;
	while (*str && ft_strchr(sep, *str))
		++str;
	if (!*str)
	{
		*last = str;
		return (0);
	}
	start = str;
	while (*str && !ft_strchr(sep, *str))
		++str;
	if (!*str)
		*last = str;
	else
	{
		*str++ = 0;
		*last = str;
	}
	return (start);
}
