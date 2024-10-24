/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_expansion_dollar.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:30:01 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 00:16:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

static int	ft_ischar_identifier(char c)
{
	return (c == '_' || ft_isalnum(c));
}

int	msh_execute_exit_status_get(void);

static void	process_question(char **new_strptr, int *i)
{
	char	*buf;

	buf = NULL;
	buf = ft_itoa(msh_execute_exit_status_get());
	if (!buf)
		msh_perror_exit("msh_parse_expansion_dollar", "process_question",
			"malloc fail.", EXIT_FAILURE);
	ft_strappend(new_strptr, buf);
	ft_memdel((void **)&buf);
	(*i)++;
}

static void	process_identifier(t_list *env_list, char *str, int *i,
		char **new_strptr)
{
	int		start;
	char	*key;
	char	*value;

	if (str[*i] == '?')
		return (process_question(new_strptr, i));
	start = *i;
	while (str[*i] && ft_ischar_identifier(str[*i]))
		++*i;
	key = NULL;
	key = ft_substr(str, start, *i - start);
	if (!key)
		msh_perror_exit("msh_parse_expansion_dollar", "process_identifier: key",
			"malloc fail.", EXIT_FAILURE);
	value = NULL;
	value = msh_env_getvar(env_list, key);
	ft_memdel((void **) &key);
	if (value)
	{
		ft_strappend(new_strptr, value);
		if (!*new_strptr)
			msh_perror_exit("msh_parse_expansion_dollar",
				"process_identifier: new_strptr", "malloc fail.", EXIT_FAILURE);
	}
}

static void	msh_parse_expansion_dollar_helper(char **strptr, int start, int i,
		char **new_strptr)
{
	msh_parse_expansion_utils_strappend(strptr, start, i, new_strptr);
	ft_memdel((void **) strptr);
	*strptr = *new_strptr;
}

/*
 * Environment variables cannot be special chars
 *
 * If flag is even, $ should be expanded. If odd, $ should be treated as string
 * 
 * (*strptr)[i + 1] check is to account for args ending with '$'.
 *
 * quote = 0 is to ignore quotes.
 */
void	msh_parse_expansion_dollar(char **strptr, t_list *env_list, int quote)
{
	int		dquote_flag;
	int		start;
	int		i;
	char	*new_str;

	dquote_flag = 0;
	start = 0;
	i = -1;
	new_str = NULL;
	while ((*strptr)[++i])
	{
		if (quote && (*strptr)[i] == '\"')
			++dquote_flag;
		if (quote && (*strptr)[i] == '\'' && !(dquote_flag % 2))
			while ((*strptr)[++i] != '\'')
				;
		if ((*strptr)[i] == '$' && (ft_ischar_identifier((*strptr)[i + 1])
			|| (*strptr)[i + 1] == '?'))
		{
			msh_parse_expansion_utils_strappend(strptr, start, i++, &new_str);
			process_identifier(env_list, *strptr, &i, &new_str);
			start = i--;
		}
	}
	msh_parse_expansion_dollar_helper(strptr, start, i, &new_str);
}