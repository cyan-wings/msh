/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:57:05 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:24:43 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_env.h"

void	msh_env_print(t_list *env_list)
{
	const t_list	*curr = NULL;
	const t_env		*curr_env = NULL;

	curr = env_list;
	if (!curr)
		msh_perror("debug", "msh_env_print", "env_list is NULL.");
	while (curr)
	{
		curr_env = (t_env *)curr->content;
		ft_putstr_fd(curr_env->key, STDIN_FILENO);
		ft_putchar_fd('=', STDIN_FILENO);
		ft_putendl_fd(curr_env->val, STDIN_FILENO);
		curr = curr->next;
	}
	return ;
}
