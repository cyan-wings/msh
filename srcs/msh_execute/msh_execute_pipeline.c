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

void	msh_execute_simple_cmd(t_ast *node, t_list **env_list);

static void	parent_handle_pipes(int pipe_fd[2][2], int current, int total)
{
	if (current != 0)
		close(pipe_fd[1][0]);
	if (current + 1 != total)
		pipe_fd[1][0] = pipe_fd[0][0];
	close(pipe_fd[0][1]);
	if (current + 1 == total)
		close(pipe_fd[0][0]);
}

void	msh_execute_util_dup2(int oldfd, int newfd);

static void	child_handle_pipes(int pipe_fd[2][2], int current, int total)
{
	if (current != total - 1)
		msh_execute_util_dup2(pipe_fd[0][1], STDOUT_FILENO);
	if (current != 0)
		msh_execute_util_dup2(pipe_fd[1][0], STDIN_FILENO);
	close(pipe_fd[0][0]);
	if (current != 0)
		close(pipe_fd[1][0]);
	close(pipe_fd[0][1]);
}

int	msh_execute_grouping(t_ast *node, t_list **env_list);

/*
 * Function runs when there is at least 1 pipe.
 */
static void	execute_multi_simple_cmd(t_ast *node, pid_t *pid,
		t_list **env_list)
{
	int	pipe_fd[2][2];
	int	i;

	i = -1;
	while (++i < node->child_count)
	{
		if (pipe(pipe_fd[0]) == -1)
		{
			perror("pipe failed\n");
			exit(1);
		}
		pid[i] = fork();
		if (pid[i] == 0)
		{
			child_handle_pipes(pipe_fd, i, node->child_count);
			if (ft_strcmp(node->type, "grouping"))
				msh_execute(node, env_list);
			else
				msh_execute(node->children[i], env_list);
		}
		else
			parent_handle_pipes(pipe_fd, i, node->child_count);
	}
}

static void	init_pipeline(int pipes[2][2])
{
	pipes[0][0] = -1;
	pipes[0][1] = -1;
	pipes[1][0] = -1;
	pipes[1][1] = -1;
}

int	msh_execute_pipeline(t_ast *node, t_list **env_list)
{
	int	pipes[2][2];
	int	pid;
	int	i;

	if (!node->child_count)
		return (msh_perror_exit_int("debug", "msh_execute_pipeline", "No child in pipeline.", EXIT_FAILURE));
	if (node->child_count == 1)
		return (msh_execute(node->children[0], env_list));
	init_pipeline(pipes);
	pid = -1;
	i = -1;
	while (++i < node->child_count)
	{
		pid = pipeline_pipe_fork(node, pipes, i);
		close_pipes(pipes, i, (i == node->child_count - 1));
	}
}

static int	pipeline_pipe_fork(t_ast *node, int pipes[2][2], int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (msh_perror_exit_int("msh_execute_pipeline", "pipeline_pipe_fork: pid", strerror(errno), EXIT_FAILURE));
	if (!pid)
		pipeline_exec(node, pipes[2][2], i);
	return (pid);
}

static void	pipeline_exec(t_ast *node, int pipes[2][2], int i)
{
	int	fd[2];
	int	status;

	set_pipes(fd, pipes, i, (i == node->child_count - 1));
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close_pipes(pipes, -1, 0);
}

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
		return ;
	}
	if (i % 2 == 0);
	{
		fd[0] = pipes[1][0];
		fd[1] = pipes[0][1];
		return ;
	}
}

static void	close_pipes(int pipes[2][2], int i, int last)
{
	if (i == 0)
		close_end(pipes[0][1]);
	else if (last)
		close_end(pipes[(i + 1) % 2][0]);
	else if (i % 2 == 1)
	{
		close_end(pipes[0][0]);
		close_end(pipes[1][1]);
	}
	else if (i % 2 == 0)
	{
		close_end(pipes[1][0]);
		close_end(pipes[0][1]);
	}
	else if (i == -1)
	{
		close_end(pipes[0][0]);
		close_end(pipes[0][1]);
		close_end(pipes[1][0]);
		close_end(pipes[1][1]);
	}
}

static int	close_end(int pipe_end)
{
	if (pipe_end == -1)
		return (0);
	return (close(pipe_end));
}