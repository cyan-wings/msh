/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:40:51 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:41:07 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static void	msh_t_env_clear(void *content)
{
	t_env	*env_var;
	char	*k;
	char	*v;

	env_var = (t_env *) content;
	k = env_var->key;
	v = env_var->val;
	ft_memdel((void **) &k);
	ft_memdel((void **) &v);
	free(content);
	return ;
}

void	msh_env_free(t_list **env_list)
{
	ft_lstclear(env_list, msh_t_env_clear);
	//system("leaks msh -q");
	return ;
}
