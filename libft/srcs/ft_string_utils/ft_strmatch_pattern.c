/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmatch_pattern.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:08:07 by myeow             #+#    #+#             */
/*   Updated: 2024/07/12 15:07:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string_utils.h"

static void	found_match(int *i, int *j)
{
	++*i;
	++*j;
}

static void	start_from_last_wildcard(int *i, int *j,
		int *startIndex, int *match)
{
	*j = *startIndex + 1;
	++*match;
	*i = *match;
}

/*
 * Usually a wildcard would take from of '*'.
 * This function assumes that the '*' char value for pattern matching 
 * has been converted to -1.
 */
int	ft_strmatch_pattern_helper(char *str, char *pattern, int startIndex,
		int match)
{
	const int	n = ft_strlen(str);
	const int	m = ft_strlen(pattern);
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < n)
	{
		if (j < m && pattern[j] == str[i])
			found_match(&i, &j);
		else if (j < m && pattern[j] == -1)
		{
			startIndex = j;
			match = i;
			++j;
		}
		else if (startIndex != -1)
			start_from_last_wildcard(&i, &j, &startIndex, &match);
		else
			return (0);
	}
	while (j < m && pattern[j] == -1)
		++j;
	return (j == m);
}

int	ft_strmatch_pattern(char *str, char *pattern)
{
	return (ft_strmatch_pattern_helper(str, pattern, -1, 0));
}
