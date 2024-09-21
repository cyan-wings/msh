/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:42:25 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 15:23:12 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

static char	*find_equals(char *env_str)
{
	while (*env_str != '=')
		++env_str;
	return (env_str);
}

void	msh_env_init(t_list **env_list)
{
	extern char	**environ;
	char		*equals_symbol;
	char		*k;
	char		*v;

	if (!env_list)
	{
		msh_perror("debug", "msh_env_init", "env_list is NULL.");
		return ;
	}
	if (!environ)
		msh_perror_exit("msh_env_init", NULL,
			"No environment variable.", EXIT_FAILURE);
	while (*environ)
	{
		equals_symbol = find_equals(*environ);
		k = ft_memalloc(equals_symbol - *environ + 1);
		v = ft_memalloc(ft_strlen(equals_symbol));
		if (!k || !v)
			msh_perror_exit("msh_env_init", NULL, "malloc fail.", EXIT_FAILURE);
		ft_strlcpy(k, *environ, equals_symbol - *environ + 1);
		ft_strlcpy(v, equals_symbol + 1, ft_strlen(equals_symbol));
		msh_env_setvar(env_list, k, v);
		++environ;
	}
}
