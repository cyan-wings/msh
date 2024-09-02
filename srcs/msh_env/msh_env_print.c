/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:57:05 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 19:02:24 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_env_print(t_list *env_list)
{
	const t_list	*curr = 0;
	const t_env		*curr_env = 0;

	curr = env_list;
	if (!curr)
		ft_putendl_fd("env list unavailable.", 1);
	while (curr)
	{
		curr_env = (t_env *)curr->content;
		ft_putstr_fd(curr_env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(curr_env->val, 1);
		curr = curr->next;
	}
	return ;
}
