/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:42:25 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:44:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

static char	*find_equals(char *env_str)
{
	while (*env_str != '=')
		++env_str;
	return (env_str);
}

void	msh_env_init(t_list **env_list, char **envp)
{
	int			i;
	char		*equals_symbol;
	char		*k;
	char		*v;

	if (!env_list)
		return (msh_perror_exit("debug", "msh_env_init", "env_list is NULL.",
				EXIT_FAILURE));
	if (!envp)
		return (msh_perror_exit("msh_env_init", NULL,
				"No environment variable.", EXIT_FAILURE));
	i = -1;
	while (envp[++i])
	{
		equals_symbol = find_equals(envp[i]);
		k = msh_utils_memalloc(equals_symbol - envp[i] + 1, "msh_env_init",
				"k");
		v = msh_utils_memalloc(ft_strlen(equals_symbol), "msh_env_init", "v");
		ft_strlcpy(k, envp[i], equals_symbol - envp[i] + 1);
		ft_strlcpy(v, equals_symbol + 1, ft_strlen(equals_symbol));
		msh_env_setvar(env_list, k, v);
		ft_memdel((void **)&k);
		ft_memdel((void **)&v);
	}
}
