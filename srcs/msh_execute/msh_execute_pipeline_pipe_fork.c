/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline_pipe_fork.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:36:36 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 07:38:40 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static void	set_pipes(int fd[2], int pipes[2][2], int i, int last)
{
	if (!i)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = pipes[0][1];
		return ;
	}
	if (last)
	{
		fd[0] = pipes[(i + 1) % 2][0];
		fd[1] = STDOUT_FILENO;
		return ;
	}
	if (i % 2 == 1)
	{
		fd[0] = pipes[0][0];
		fd[1] = pipes[1][1];
	}
	else
	{
		fd[0] = pipes[1][0];
		fd[1] = pipes[0][1];
	}
}

//Check leak before exit
static void	pipeline_exec(t_ast *node, int pipes[2][2], int i,
		t_list **env_list)
{
	int	fd[2];
	int	status;

	set_pipes(fd, pipes, i, (i == node->child_count - 1));
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	msh_execute_pipeline_close(pipes, -1, 0);
	if (!ft_strcmp(node->children[i]->type, "simple_command"))
		msh_execute_pipeline_simple_cmd(node, env_list, 0);
	else if (!ft_strcmp(node->children[i]->type, "grouping"))
	{
		status = msh_execute_grouping(node->children[i], env_list);
		exit(status);
	}
}

int	msh_execute_pipeline_pipe_fork(t_ast *node, int pipes[2][2], int i,
				t_list **env_list)
{
	int	pid;

	if (i != node->child_count - 1 && pipe(pipes[i % 2]) < 0)
		return (msh_perror_exit_int("msh_execute_pipeline",
				"pipeline_pipe_fork: pipe", strerror(errno),
				EXIT_FAILURE));
	pid = fork();
	if (pid == -1)
		return (msh_perror_exit_int("msh_execute_pipeline",
				"pipeline_pipe_fork: pid", strerror(errno), EXIT_FAILURE));
	if (!pid)
		pipeline_exec(node, pipes, i, env_list);
	return (pid);
}
