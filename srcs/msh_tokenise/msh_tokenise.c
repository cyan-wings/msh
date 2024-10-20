/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tokenise.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:58:44 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 19:19:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_tokenise.h"

void	msh_tokenise_insert_token(char *str, t_list **token_list);

/*
 * This function is to check whether its quoted.
 * Input is incremented at the beginning because input will be
 * the quote character when this function enters.
 * Return:
 * 		Pointer to the closing quote character if present,
 * 		null if not.
 */
static char	*get_close_quote(char *ptr, char quote_type)
{
	++ptr;
	while (*ptr && *ptr != quote_type)
		++ptr;
	if (*ptr == quote_type)
		return (ptr);
	return (NULL);
}

/*
 * Similar to ft_split_tok, but ignoring delims in quotes.
 */
int	msh_tokenise(char *input, t_list **token_list)
{
	const char	*sep = " \t\r\n\v\f";
	char		*start_ptr;

	if (!input || !token_list)
		return (ERROR);
	while (*input && ft_strchr(sep, *input))
		++input;
	start_ptr = input;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
			input = get_close_quote(input, *input);
		if (!input)
			return (ERROR);
		if (!ft_strchr(sep, *input) && (!input[1] || ft_strchr(sep, input[1])))
		{
			if (input[1])
				*++input = 0;
			msh_tokenise_insert_token(start_ptr, token_list);
		}
		if (ft_strchr(sep, *input) && !ft_strchr(sep, input[1]))
			start_ptr = input + 1;
		++input;
	}
	return (0);
}
