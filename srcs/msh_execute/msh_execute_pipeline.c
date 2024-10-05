/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:59 by myeow             #+#    #+#             */
/*   Updated: 2024/09/30 14:33:31 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

int	msh_execute(t_ast *node, t_list **env_list);

static void	init_pipeline(int pipes[2][2])
{
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

int	msh_execute_pipeline_pipe_fork(t_ast *node, int pipes[2][2], int i,
				t_list **env_list);

static int	pipeline_wait_pid(int last_pid)
{
	int	pid;
	int	status;

	status = msh_execute_wait_pid(last_pid, NULL);
	pid = 0;
	while (pid >= 0)
		pid = wait(NULL);
	errno = 0;
	return (status);
}

int	msh_execute_pipeline(t_ast *node, t_list **env_list, int subshell_flag)
{
	int	pipes[2][2];
	int	pid;
	int	i;

	if (!node->child_count)
		return (msh_perror_exit_int("debug", "msh_execute_pipeline",
				"No child nodes in pipeline.", EXIT_FAILURE));
	if (node->child_count == 1)
		return (msh_execute_simple_cmd(node->children[0], env_list));
	init_pipeline(pipes);
	pid = -1;
	i = -1;
	while (++i < node->child_count)
	{
		pid = pipeline_pipe_fork(node, pipes, i, env_list);
		close_pipes(pipes, i, (i == node->child_count - 1));
	}
	return (pipeline_wait_pid(pid));
}