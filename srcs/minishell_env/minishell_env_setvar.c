/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_setvar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:58:08 by myeow             #+#    #+#             */
/*   Updated: 2024/05/27 22:38:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_env_setvar(t_list **env_list, char *k, char *v)
{
	t_list	*curr;
	t_env	*env_var;

	if (!env_list)
		return ;
	curr = *env_list;
	while(curr)
	{
		env_var = (t_env *) curr->content;
		if (!ft_strcmp(env_var->key, k))
		{
			env_var->val = v;
			return ;
		}
		curr = curr->next;
	}
	env_var = (t_env *) ft_memalloc(sizeof(t_env));
	if (!env_var)
		return (minishell_perror_exit("Env var no mem", EXIT_FAILURE));
	env_var->key = k;
	env_var->val = v;
	ft_lstadd_back(env_list, ft_lstnew(env_var));
	return ;
}
