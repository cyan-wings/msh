/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:40:51 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 16:46:37 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_env_free_t_env(void *content);

//Use system("leaks msh -q"); after ft_lstclear.
void	msh_env_free(t_list **env_list)
{
	ft_lstclear(env_list, msh_env_free_t_env);
	return ;
}
