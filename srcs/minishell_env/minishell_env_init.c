/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:48:43 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 23:12:26 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_equals(char *env_str)
{
	while (*env_str != '=')
		++env_str;
	return (env_str);
}

void	minishell_env_init(t_list **env_list)
{
	extern char	**environ;
	char		*equals_symbol;
	char		*k;
	char		*v;

	if (!environ)
		return (minishell_perror_exit("Environ not available", EXIT_FAILURE));
	while (*environ)
	{
		equals_symbol = find_equals(*environ);
		k = ft_memalloc(equals_symbol - *environ + 1);
		v = ft_memalloc(ft_strlen(equals_symbol));
		if (!k || !v)
			return (minishell_perror_exit("Env init key val no mem",
					EXIT_FAILURE));
		ft_strlcpy(k, *environ, equals_symbol - *environ + 1);
		ft_strlcpy(v, equals_symbol + 1, ft_strlen(equals_symbol));
		minishell_env_setvar(env_list, k, v);
		++environ;
	}
	env_list = 0;
	return ;
}
