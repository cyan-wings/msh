/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_grouping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:24:31 by myeow             #+#    #+#             */
/*   Updated: 2024/09/17 16:48:38 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

int	msh_execute_wait_pid(int prev_pid, char *name);

int	msh_execute_grouping(t_ast *node, t_list **env_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		msh_perror(strerror(errno));
		errno = 0;
		return (-1);
	}
	if (pid == 0)
	{
		status = msh_execute(node->children[0], env_list);
		exit(status);
	}
	return (msh_execute_wait_pid(pid, NULL));
}
/*
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid failed in subshell");
		if (WIFEXITED(status))
			WEXITSTATUS(status);
	}
*/
