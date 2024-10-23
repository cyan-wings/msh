/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:57:05 by myeow             #+#    #+#             */
/*   Updated: 2024/10/23 16:35:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

void	msh_env_print(t_list *env_list, int export_flag)
{
	const t_list	*curr = NULL;
	const t_env		*curr_env = NULL;

	curr = env_list;
	if (!curr)
		msh_perror("debug", "msh_env_print", "env_list is NULL.");
	while (curr)
	{
		if (export_flag)
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		curr_env = (t_env *)curr->content;
		ft_putstr_fd(curr_env->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(curr_env->val, STDOUT_FILENO);
		curr = curr->next;
	}
	return ;
}
