/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_delvar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:35:43 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:12:44 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"
#include "ft_mem_utils.h"

void	msh_env_free_t_env(void *content);

/*
 * @params:
 * 		k: Key to delete the environment variable.
 */
void	msh_env_delvar(t_list **env_list, char *k)
{
	t_list	*prev;
	t_list	*curr;

	if (!env_list || !k)
		return ;
	prev = 0;
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
			ft_memdel((void **) &curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
