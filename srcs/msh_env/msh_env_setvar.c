/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_setvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:42:36 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:10:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"
#include "ft_mem_utils.h"

void	msh_env_setvar(t_list **env_list, char *k, char *v)
{
	t_list	*curr;
	t_env	*env_var;

	if (!env_list)
		return ;
	curr = *env_list;
	while (curr)
	{
		env_var = (t_env *) curr->content;
		if (!ft_strcmp(env_var->key, k))
		{
			ft_memdel((void **)&env_var->val);
			env_var->val = v;
			return ;
		}
		curr = curr->next;
	}
	env_var = (t_env *) ft_memalloc(sizeof(t_env));
	if (!env_var)
		return (msh_perror_exit("Env var no mem", EXIT_FAILURE));
	env_var->key = k;
	env_var->val = v;
	ft_lstadd_back(env_list, ft_lstnew(env_var));
	return ;
}
