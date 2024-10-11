/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_exit_status_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:15:10 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 07:15:28 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

int	*msh_execute_exit_status_ptr(void);

void	msh_execute_exit_status_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*msh_execute_exit_status_ptr() = status;
}
