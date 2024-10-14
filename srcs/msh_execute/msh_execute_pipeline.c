/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:59 by myeow             #+#    #+#             */
/*   Updated: 2024/10/07 08:00:49 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static int	check_param(t_ast *node, t_list **env_list)
{
	int	flag;

	flag = 1;
	if (!node)
	{
		msh_perror("debug", "msh_execute_pipeline", "node is NULL.");
		flag = 0;
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute_pipeline", "env_list is NULL.");
		flag = 0;
	}
	if (node && !node->child_count)
	{
		msh_perror("debug", "msh_execute_pipeline",
			"No child nodes in pipeline.");
		flag = 0;
	}
	if (node && ft_strcmp(node->type, "pipeline"))
	{
		msh_perror("debug", "msh_execute_pipeline", "node is not pipeline.");
		flag = 0;
	}
	return (flag);
}

int		msh_execute_simple_cmd(t_ast *node, t_list **env_list,
				int subshell_flag);

int		msh_execute_grouping(t_ast *node, t_list **env_list,
				int subshell_flag);

static int	execute_pipeline_single(t_ast *child_node, t_list **env_list,
		int subshell_flag)
{
	if (!ft_strcmp(child_node->type, "simple_command"))
		return (msh_execute_simple_cmd(child_node, env_list,
				subshell_flag));
	else if (!ft_strcmp(child_node->type, "grouping"))
		return (msh_execute_grouping(child_node, env_list,
				subshell_flag));
	else
		return (msh_perror_exit_int("debug",
				"msh_execute_pipeline: execute_pipeline_single",
				"Unknown node type", EXIT_FAILURE));
}

static void	init_pipeline(int pipes[2][2])
{
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

int		msh_execute_pipeline_pipe_fork(t_ast *node, int pipes[2][2], int i,
				t_list **env_list);

void	msh_execute_pipeline_close(int pipes[2][2], int i, int last);

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

int	msh_execute_pipeline(t_ast *node, t_list **env_list,
		int subshell_flag)
{
	int	pipes[2][2];
	int	pid;
	int	i;

	if (!check_param(node, env_list))
		return (ERROR);
	if (node->child_count == 1)
		return (execute_pipeline_single(node->children[0], env_list,
				subshell_flag));
	init_pipeline(pipes);
	pid = -1;
	i = -1;
	while (++i < node->child_count)
	{
		pid = msh_execute_pipeline_pipe_fork(node, pipes, i, env_list);
		if (pid == ERROR)
		{
			msh_execute_pipeline_close(pipes, -1, 0);
			break ;
		}
		msh_execute_pipeline_close(pipes, i, (i == node->child_count - 1));
	}
	return (pipeline_wait_pid(pid));
}
