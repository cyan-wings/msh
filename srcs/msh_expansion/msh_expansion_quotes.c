/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:20:39 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 17:54:27 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expansion.h"

static void	find_closing_quotes(char **strptr, char quote_type, int *i)
{
	while ((*strptr)[*i] != quote_type)
		++*i;
}

static void	msh_expansion_quotes_helper(char **strptr, char **new_str)
{
	int		start;
	char	quote_type;
	int		i;

	start = 0;
	quote_type = 0;
	i = -1;
	while ((*strptr)[++i])
	{
		if ((*strptr)[i] == '\'' || (*strptr)[i] == '\"')
		{
			msh_expansion_utils_strappend(strptr, start, i, new_str);
			quote_type = (*strptr)[i];
			start = ++i;
			find_closing_quotes(strptr, quote_type, &i);
			msh_expansion_utils_strappend(strptr, start, i, new_str);
			start = i + 1;
		}
	}
	msh_expansion_utils_strappend(strptr, start, i, new_str);
}

/*
 * Function that performs quote removals
 */
void	msh_expansion_quotes(char **strptr)
{
	char	*new_str;

	new_str = NULL;
	msh_expansion_quotes_helper(strptr, &new_str);
	ft_memdel((void **)strptr);
	*strptr = new_str;
}
