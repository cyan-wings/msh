/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:30:01 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 15:28:40 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expansion.h"

static int	ft_ischar_identifier(char c)
{
	return (c == '_' || ft_isalnum(c));
}

static void	process_identifier(t_list *env_list, char *str, int *i,
		char **new_strptr)
{
	int		start;
	char	*key;
	char	*value;

	start = *i;
	while (str[*i] && ft_ischar_identifier(str[*i]))
		++*i;
	key = NULL;
	key = ft_substr(str, start, *i - start);
	if (!key)
		msh_perror_exit("msh_expansion_dollar", "process_identifier: key",
			"malloc fail.", EXIT_FAILURE);
	value = NULL;
	value = msh_env_getvar(env_list, key);
	ft_memdel((void **) &key);
	if (value)
		ft_strappend(new_strptr, value);
	else
		ft_strappend(new_strptr, "");
	if (!*new_strptr)
		msh_perror_exit("msh_expansion_dollar",
			"process_identifier: new_strptr",
			"malloc fail.", EXIT_FAILURE);
}

static void	msh_expansion_dollar_helper(char **strptr, int start, int i,
		char **new_strptr)
{
	msh_expansion_utils_strappend(strptr, start, i, new_strptr);
	ft_memdel((void **) strptr);
	*strptr = *new_strptr;
}

/*
 * Environment variables cannot be special chars
 *
 * If flag is even, $ should be expanded. If odd, $ should be treated as string
 */
void	msh_expansion_dollar(char **strptr, t_list *env_list)
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
		if ((*strptr)[i] == '\"')
			++dquote_flag;
		if ((*strptr)[i] == '\'' && !(dquote_flag % 2))
			while ((*strptr)[++i] != '\'')
				;
		if ((*strptr)[i] == '$')
		{
			msh_expansion_utils_strappend(strptr, start, i++, &new_str);
			process_identifier(env_list, *strptr, &i, &new_str);
			start = i--;
		}
	}
	msh_expansion_dollar_helper(strptr, start, i, &new_str);
}
