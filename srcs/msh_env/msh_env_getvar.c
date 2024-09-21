/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_getvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:41:49 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:23:20 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

static int	check_null_param(t_list *env_list, char *k)
{
	int	flag;

	flag = 1;
	if (!env_list)
	{
		msh_perror("debug", "msh_env_getvar", "env_list is NULL.");
		flag = 0;
	}
	if (!k)
	{
		msh_perror("debug", "msh_env_getvar", "k is NULL.");
		flag = 0;
	}
	return (flag);
}

char	*msh_env_getvar(t_list *env_list, char *k)
{
	t_env	*env_var;

	if (!check_null_param(env_list, k))
		return (NULL);
	env_var = NULL;
	while (env_list)
	{
		env_var = (t_env *)env_list->content;
		if (!ft_strcmp(k, env_var->key))
			return (env_var->val);
		env_list = env_list->next;
	}
	return (NULL);
}
