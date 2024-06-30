/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_word_string.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:38:32 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 22:51:40 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define SQUOTE '\''
#define DQUOTE '\"'

static int	ft_isprint_except_a_b(char c, char a, char b)
{
	if (c == a || c == b)
		return (0);
	return (ft_isprint(c));
}

static int	characters_except_a_b(char *str, int *idx, char a, char b)
{
	if (str[*idx] == 0)
		return (1);
	if (ft_isprint_except_a_b(str[*idx], a, b))
	{
		++*idx;
		return (characters_except_a_b(str, idx, a, b));
	}
	return (0);
}

static int	quote_string(char *str, int *idx, char quote_type)
{
	if (str[*idx] == 0)
		return (0);
	if (str[*idx] == quote_type)
	{
		++*idx;
		while (ft_isprint_except_a_b(str[*idx], quote_type, -1))
			++*idx;
		return (str[*idx] == quote_type);
	}
	return (0);
}

static int	string_tail(char *str, int *idx)
{
	if (str[*idx] == 0)
		return (1);
	if (characters_except_a_b(str, idx, SQUOTE, DQUOTE))
		return (string_tail(str, idx));
	if (quote_string(str, idx, DQUOTE))
	{
		++*idx;
		return (string_tail(str, idx));
	}
	if (quote_string(str, idx, SQUOTE))
	{
		++*idx;
		return (string_tail(str, idx));
	}
	return (0);
}

int	minishell_parse_word_string(char *str, int *idx)
{
	int	start_idx;

	start_idx = *idx;
	if (ft_isprint_except_a_b(str[*idx], SQUOTE, DQUOTE))
	{
		++*idx;
		return (string_tail(str, idx));
	}
	*idx = start_idx;
	if (quote_string(str, idx, DQUOTE))
	{
		++*idx;
		return (string_tail(str, idx));
	}
	*idx = start_idx;
	if (quote_string(str, idx, SQUOTE))
	{
		++*idx;
		return (string_tail(str, idx));
	}
	return (0);
}