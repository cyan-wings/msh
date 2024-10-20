/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_wait_pid.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:11:04 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 21:39:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static void	print_error_sig(int sig, char *name)
{
	if (sig == SIGABRT)
		msh_perror(name, "Abort program", "6");
	else if (sig == SIGBUS)
		msh_perror(name, "Bus error", "10");
	else if (sig == SIGSEGV)
		msh_perror(name, "Segmentation fault", "11");
	else if (sig == SIGTERM)
		msh_perror(name, "Terminated", "15");
}

/*
 * WTERMSIG(status) = 3, terminated using SIGQUIT
 * WTERMSIG(status) = 2, terminated using SIGINT
 * When a process is terminated by a signal,
 * the exit status is conventionally set to 128 + signal_number.
 * This is done here to reflect that the process was killed by a signal.
 */
int	msh_execute_wait_pid(int prev_pid, char *name)
{
	int	status;
	int	sig;

	status = 0;
	if (waitpid(prev_pid, &status, 0) == -1)
		return (msh_perror_exit_int("msh_execute_wait_pid", "waitpid",
				"-1", EXIT_FAILURE));
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putendl_fd("Quit: 3", STDERR_FILENO);
		else if (sig == SIGINT)
			ft_putchar_fd('\n', STDERR_FILENO);
		print_error_sig(sig, name);
		status = 128 + sig;
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
