/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion_dollar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:30:01 by myeow             #+#    #+#             */
/*   Updated: 2024/07/11 16:17:18 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_expansion_utils_strappend(char **strptr, int start, int i,
			char **new_strptr);

int	ft_ischar_identifier(char c)
{
	return (c == '_' || ft_isalnum(c));
}

static char	*process_identifier(t_list *env_list, char *str, int start, int *i)
{
	char	*key;
	char	*value;

	while (str[*i] && ft_ischar_identifier(str[*i]))
		++*i;
	key = ft_substr(str, start, *i - start);
	value = msh_env_getvar(env_list, key);
	if (value)
		value = ft_strdup(value);
	else
		value = 0;
	ft_memdel((void **) &key);
	return (value);
}

/*
 * Environment variables cannot be special chars
 *
 * If flag is even, $ should be expanded. If odd, $ should be treated as string
 */
void	msh_expansion_dollar(char **strptr, t_list *env_list)
{
	int		dquote_flag;
	int		flag;
	int		start;
	int		i;
	char	*new_str;
	char	*temp;

	dquote_flag = 0;
	flag = 0;
	start = 0;
	i = -1;
	new_str = 0;
	while ((*strptr)[++i])
	{
		if ((*strptr)[i] == '\"')
			++dquote_flag;
		if ((*strptr)[i] == '\'' && !(dquote_flag % 2))
			++flag;
		if ((*strptr)[i] == '$' && !(flag % 2))
		{
			msh_expansion_utils_strappend(strptr, start, i, &new_str);
			start = ++i;
			temp = process_identifier(env_list, *strptr, start, &i);
			ft_strappend(&new_str, temp);
			ft_memdel((void **) &temp);
			start = i--;
		}
	}
	msh_expansion_utils_strappend(strptr, start, i, &new_str);
	ft_memdel((void **) strptr);
	*strptr = new_str;
}
