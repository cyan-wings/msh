/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_setvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:42:36 by myeow             #+#    #+#             */
/*   Updated: 2024/10/30 17:02:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

static int	check_null_param(t_list **env_list, char *k, char *v)
{
	int	flag;

	flag = 1;
	if (!env_list)
	{
		msh_perror("debug", "msh_env_setvar", "env_list is NULL.");
		flag = 0;
	}
	if (!k)
	{
		msh_perror("debug", "msh_env_setvar", "k is NULL.");
		flag = 0;
	}
	if (!v)
	{
		msh_perror("debug", "msh_env_setvar", "v is NULL.");
		flag = 0;
	}
	return (flag);
}

/*
 * Updates an environment variable or creates it if not present.
 *
 * @params
 * 		k: 	key of the env (doesn't need to be freed)
 * 		v:	value of the env (doesn't need to be freed)
 *
 */
void	msh_env_setvar(t_list **env_list, char *k, char *v)
{
	t_list	*curr;
	t_env	*env_var;

	if (!check_null_param(env_list, k, v))
		return ;
	curr = *env_list;
	while (curr)
	{
		env_var = (t_env *) curr->content;
		if (!ft_strcmp(env_var->key, k))
		{
			ft_memdel((void **)&env_var->val);
			env_var->val = msh_utils_strdup(v, "msh_env_setvar", "v");
			return ;
		}
		curr = curr->next;
	}
	env_var = (t_env *)msh_utils_memalloc(sizeof(t_env), "msh_env_setvar",
			"env_var");
	env_var->key = msh_utils_strdup(k, "msh_env_setvar", "k");
	env_var->val = msh_utils_strdup(v, "msh_env_setvar", "v");
	ft_lstadd_back(env_list, ft_lstnew(env_var));
	return ;
}
