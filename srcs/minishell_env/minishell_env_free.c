/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:46:44 by myeow             #+#    #+#             */
/*   Updated: 2024/06/28 17:46:46 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_t_env_clear(void *content)
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

void	minishell_env_free(t_list **env_list)
{
	ft_lstclear(env_list, minishell_t_env_clear);
	//system("leaks minishell -q");
	return ;
}
