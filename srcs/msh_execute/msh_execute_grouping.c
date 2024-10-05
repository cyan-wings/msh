/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_grouping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:24:31 by myeow             #+#    #+#             */
/*   Updated: 2024/09/30 13:34:54 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

int	msh_execute_wait_pid(int prev_pid, char *name);

//May want to free everything before exit.
//May want to add subshell flag for exit builtin.
int	msh_execute_grouping(t_ast *node, t_list **env_list,
		int subshell_flag __attribute((unused)))
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		msh_perror_exit("msh_execute_grouping", NULL, strerror(errno),
			EXIT_FAILURE);
		errno = 0;
		return (ERROR);
	}
	if (pid == 0)
	{
		status = msh_execute(node->children[0], env_list, 0);
		exit(status);
	}
	return (msh_execute_wait_pid(pid, NULL));
}
