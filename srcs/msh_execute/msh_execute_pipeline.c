/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:59 by myeow             #+#    #+#             */
/*   Updated: 2024/09/02 13:36:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_execute_simple_cmd(t_ast *node, t_list **env_list);

/*
 * Function runs when there are no pipes in a pipeline.
 * TODO: Do we need to run builtin without fork()?
 */
static int	execute_single_simple_cmd(t_ast *node, pid_t *pid,
		t_list **env_list)
{
	int		res;
	t_ast	*current;
	t_bif	*temp_builtin;

	current = node->children[0];
	temp_builtin = msh_builtins_get_builtin(current->children[0]->value);
	if (temp_builtin)
	{
		printf("running builtin\n");
		msh_execute_simple_cmd(current, env_list);
		return (1);
	}
	else
	{
		pid[0] = fork();
		if (pid[0] == 0)
			msh_execute_simple_cmd(current, env_list);
		res = -1;
	}
	return (res);
}

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

/*
 * Function runs when there is at least 1 pipe.
 */
static int	execute_multi_simple_cmd(t_ast *node, pid_t *pid,
		t_list **env_list)
{
	int	pipe_fd[2][2];
	int	i;
	int	status;

	i = -1;
	status = 0;
	(void)status;
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
			msh_execute_simple_cmd(node->children[i], env_list);
			break ;
		}
		else
			parent_handle_pipes(pipe_fd, i, node->child_count);
	}
	return (-1);
}

/*
 * TODO: Attempt to handle grouping from here.
 */
void	msh_execute_pipeline(t_ast *node, t_list **env_list,
			t_global *global)
{
	int		i;
	pid_t	*pid_list;
	int		status;

	pid_list = ft_calloc(node->child_count, sizeof(pid_t));
	if (node->child_count <= 1)
		execute_single_simple_cmd(node, pid_list, env_list);
	else
		execute_multi_simple_cmd(node, pid_list, env_list);
	i = -1;
	while (++i < node->child_count)
	{
		if (waitpid(pid_list[i], &status, 0) == -1)
			perror("waitpid failed");
		if (WIFEXITED(status))
		{
			global->status = WEXITSTATUS(status);
			return ;
		}
	}
	free(pid_list);
}
