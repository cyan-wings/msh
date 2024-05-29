/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_getvar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:51:47 by myeow             #+#    #+#             */
/*   Updated: 2024/05/29 20:14:44 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*minishell_env_getvar(t_list *env_list, char *k)
{
	t_env	*env_var;

	env_var = 0;
	while (env_list)
	{
		env_var = (t_env *) env_list->content;
		if (!ft_strcmp(k, env_var->key))
			return (env_var->val);
		env_list = env_list->next;
	}
	return (0);
}
