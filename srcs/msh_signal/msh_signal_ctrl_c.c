/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal_ctrl_c.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:25:20 by myeow             #+#    #+#             */
/*   Updated: 2024/10/24 19:57:01 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "msh_execute.h"
#include <signal.h>

void	msh_signal_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		msh_execute_exit_status_set(EXIT_FAILURE);
	}
}
