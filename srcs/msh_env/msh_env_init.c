/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:42:25 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:09:24 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_mem_utils.h"
#include "ft_string_utils.h"

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

	if (!environ)
		return (msh_perror_exit("Environ not available", EXIT_FAILURE));
	while (*environ)
	{
		equals_symbol = find_equals(*environ);
		k = ft_memalloc(equals_symbol - *environ + 1);
		v = ft_memalloc(ft_strlen(equals_symbol));
		if (!k || !v)
			return (msh_perror_exit("Env init key val no mem",
					EXIT_FAILURE));
		ft_strlcpy(k, *environ, equals_symbol - *environ + 1);
		ft_strlcpy(v, equals_symbol + 1, ft_strlen(equals_symbol));
		msh_env_setvar(env_list, k, v);
		++environ;
	}
	env_list = 0;
	return ;
}
