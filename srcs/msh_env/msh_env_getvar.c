/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_getvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:41:49 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:11:12 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"

char	*msh_env_getvar(t_list *env_list, char *k)
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
