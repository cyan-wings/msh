/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_expand_word.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:15:32 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 18:12:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

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

char	*msh_parse_cmd_expand_word(char *word, t_list *env_list)
{
	char	*out;
	char	*out_cpy;

	out = NULL;
	out = msh_utils_strdup(word, "msh_parse_cmd_expand_word", "out");
	format_spaces(out, 0);
	msh_parse_expansion_dollar(&out, env_list, 1);
	if (!out)
		return (NULL);
	out_cpy = NULL;
	out_cpy = msh_utils_strdup(out, "msh_parse_cmd_expand_word", "out_cpy");
	format_spaces(out_cpy, 1);
	if (format_wildcards(out_cpy))
	{
		msh_parse_expansion_quotes(&out_cpy);
		if (msh_parse_expansion_wildcards(&out_cpy))
		{
			ft_memdel((void **)&out);
			return (out_cpy);
		}
	}
	ft_memdel((void **)&out_cpy);
	msh_parse_expansion_quotes(&out);
	return (out);
}
