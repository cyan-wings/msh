/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:14:22 by myeow             #+#    #+#             */
/*   Updated: 2024/05/12 20:06:36 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"

/*
 * 1. Checks sep or (str and last) is null. (Original strtok SEGFAULTS)
 * 2. If str is null, means its not the 1st call to ft_strtok, hence using
 * 		the same reference.
 * 3. Remove delimiters at the beginning of the token.
 * 4. Check if at null.
 * 5. Mark the start of the token.
 * 6. Find the end of the token and replace the delimiter with null-terminator.
 * 7. Update the static var to after the null-terminator and return start ptr.
 */
char	*ft_strtok(char *str, const char *sep)
{
	static char	*last = 0;
	char		*start;

	if (!sep || (!str && !last))
		return (0);
	if (!str)
		str = last;
	while (*str && ft_strchr(sep, *str))
		++str;
	if (!*str)
	{
		last = 0;
		return (0);
	}
	start = str;
	while (*str && !ft_strchr(sep, *str))
		++str;
	if (!*str)
		last = str;
	else
	{
		*str++ = 0;
		last = str;
	}
	return (start);
}
