/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:37:59 by myeow             #+#    #+#             */
/*   Updated: 2024/09/07 01:20:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"

void	msh_execute_simple_cmd(t_ast *node, t_list **env_list);

/*
 * Function runs when there are no pipes in a pipeline.
 * TODO: Do we need to run builtin without fork()?
 */
static int	execute_single_simple_cmd(t_ast *node, pid_t *pid,
		t_list **env_list)
{
	int		status;
	t_ast	*current;
	t_bif	*temp_builtin;

	status = 0;
	current = NULL;
	current = node->children[0];
	temp_builtin = NULL;
	if (!ft_strcmp(current->children[0]->type, "simple_command"))
	{
		temp_builtin = msh_builtins_get_builtin(current->children[0]->value);
		if (temp_builtin)
		{
			printf("running builtin\n");
			msh_execute(current, env_list);
			return (1);
		}
	}
	else
	{
		pid[0] = fork();
		if (pid[0] == 0)
			msh_execute(current, env_list);
		status = -1;
	}
	return (status);
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

/*
 * TODO: Attempt to handle grouping from here.
 */
//			t_global *global __attribute((unused)))
int	msh_execute_pipeline(t_ast *node, t_list **env_list)
{
	int		i;
	pid_t	*pid_list;
	int		status;
	int 	should_wait;

	pid_list = ft_calloc(node->child_count, sizeof(pid_t));
	should_wait = 0
	if (node->child_count <= 1)
		should_wait = execute_single_simple_cmd(node, pid_list, env_list);
	else
		execute_multi_simple_cmd(node, pid_list, env_list);
	i = -1;
	while (++i < node->child_count)
	{
		if (waitpid(pid_list[i], &status, 0) == -1)
			perror("waitpid failed");
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
	free(pid_list);
	return (0);
}
