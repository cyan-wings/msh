/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_delvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:35:43 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:21:28 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

void	msh_env_free_t_env(void *content);

static int	check_null_param(t_list **env_list, char *k)
{
	int	flag;

	flag = 1;
	if (!env_list)
	{
		msh_perror("debug", "msh_env_delvar", "env_list is NULL.");
		flag = 0;
	}
	if (!k)
	{
		msh_perror("debug", "msh_env_delvar", "k is NULL.");
		flag = 0;
	}
	return (flag);
}

/*
 * @params:
 * 		k: Key to delete the environment variable.
 */
void	msh_env_delvar(t_list **env_list, char *k)
{
	t_list	*prev;
	t_list	*curr;

	if (!check_null_param(env_list, k))
		return ;
	prev = NULL;
	curr = *env_list;
	while (curr)
	{
		if (!ft_strcmp(((t_env *)curr->content)->key, k))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env_list = curr->next;
			msh_env_free_t_env(curr->content);
			curr->content = NULL;
			ft_memdel((void **) &curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
