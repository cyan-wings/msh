/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_util_dup2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:29:42 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 20:27:57 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

void	msh_execute_util_dup2(int oldfd, int newfd)
{
	int	res;

	res = dup2(oldfd, newfd);
	if (res == -1)
		msh_perror_exit("msh_execute_util_dup2", NULL,
			"dup2 fail.", EXIT_FAILURE);
}
