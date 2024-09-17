/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_wait_pid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:11:04 by myeow             #+#    #+#             */
/*   Updated: 2024/09/17 16:33:36 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <signal.h>
#include <sys/wait.h>

static void	print_error_signal_helper(char *name, char *msg)
{
	if (name)
		msh_perror(name);
	if (msg)
		msh_perror(msg);
}

static void	print_error_signal(int signal, char *name)
{
	if (signal == SIGABRT)
		print_error_signal_helper(name, ": Abort program: 6");
	else if (signal == SIGBUS)
		print_error_signal_helper(name, ": Bus error: 10");
	else if (signal == SIGSEGV)
		print_error_signal_helper(name, ": Segmentation fault: 11");
	else if (signal == SIGTERM)
		print_error_signal_helper(name, ":Terminated: 15");
}

int	msh_execute_wait_pid(int prev_pid, char *name)
{
	int	status;

	status = 0;
	waitpid(prev_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		else if (WTERMSIG(status) == 2)
			ft_putchar_fd('\n', STDERR_FILENO);
		print_error_signal(WTERMSIG(status), name);
		status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
