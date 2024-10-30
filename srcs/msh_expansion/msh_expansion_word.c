/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:15:32 by myeow             #+#    #+#             */
/*   Updated: 2024/10/30 17:47:09 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expansion.h"

//flag = 0, for <space> to SPACE_R
//flag = 1, for SPACE_R to <space>
static void	format_spaces(char *str, int flag)
{
	if (!flag)
	{
		while (*str)
		{
			if (*str == ' ')
				*str = SPACE_R;
			++str;
		}
	}
	else
	{
		while (*str)
		{
			if (*str == SPACE_R)
				*str = ' ';
			++str;
		}
	}
}

/*
 * The * character is replaced with a -1 character value because it is
 * possible for a filename to include the * character.
 * The -1 will then be used later for pattern matching for 0-any chars.
 */
static int	format_wildcards(char *str)
{
	int		flag;
	char	quote_type;

	flag = 0;
	quote_type = 0;
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			quote_type = *str;
			++str;
			while (*str != quote_type)
				++str;
		}
		if (*str == '*')
		{
			*str = -1;
			flag = 1;
		}
		++str;
	}
	return (flag);
}

static char	*msh_expansion_word_helper(char *out)
{
	if (!out)
		out = msh_utils_memalloc(1, "msh_parse_cmd_expand_word",
				"msh_parse_cmd_expand_word_helper");
	return (out);
}

/*
 * 	Handles the expansion process.
 * 	
 * 	Process:
 * 		(1) If spaces are found, change them to SPACE_R.
 * 		(2) Expand all the $ sign.
 * 		(3) Create a copy and change SPACE_R back to space.
 * 		(4) Quote and wildcard expand to check if the copy
 * 			contains wildcards.
 * 		(5) Free the copy and quote expand the original
 * 			string.
 * 		(6) IF NULL, a empty string must be returned.
 * 
 * 	Notes:
 * 		(1) When a space is found in a WORD, that WORD will consider as
 * 			a single argument.
 * 			Ex:
 * 				export "-l -a "
 * 				ls "-t "
 * 			will yield an error due to recognising "-l -a ""-t " as a
 * 			single argument.
 * 		(2) 	export "-l -a "
 * 				ls "-t"
 * 			will yield 3 arguments: -l -a -t
 * 		(3) '*' has to convert to -1 since '*' can be part of a file name.
 */
char	*msh_expansion_word(char *word, t_list *env_list)
{
	char	*out;
	char	*out_cpy;

	out = NULL;
	out = msh_utils_strdup(word, "msh_parse_cmd_expand_word", "out");
	format_spaces(out, 0);
	msh_expansion_dollar(&out, env_list, 1);
	if (!out)
		return (NULL);
	out_cpy = NULL;
	out_cpy = msh_utils_strdup(out, "msh_parse_cmd_expand_word", "out_cpy");
	format_spaces(out_cpy, 1);
	if (format_wildcards(out_cpy))
	{
		msh_expansion_quotes(&out_cpy);
		if (msh_expansion_wildcards(&out_cpy))
		{
			ft_memdel((void **)&out);
			return (out_cpy);
		}
	}
	ft_memdel((void **)&out_cpy);
	msh_expansion_quotes(&out);
	return (msh_expansion_word_helper(out));
}
