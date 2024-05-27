/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:56:46 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 22:14:02 by myeow            ###   ########.fr       */
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
	return ;
}
