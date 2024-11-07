/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline_pipe_fork.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:36:36 by myeow             #+#    #+#             */
/*   Updated: 2024/10/21 15:38:15 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static void	set_pipes(int fd[2], int pipes[2][2], int i, int last)
{
	if (i == 0)
	{
		fd[0] = STDIN_FILENO;
		fd[1] = pipes[0][1];
	}
	else if (last)
	{
		fd[0] = pipes[(i + 1) % 2][0];
		fd[1] = STDOUT_FILENO;
	}
	else if (i % 2 == 1)
	{
		fd[0] = pipes[0][0];
		fd[1] = pipes[1][1];
	}
	else if (i % 2 == 0)
	{
		fd[0] = pipes[1][0];
		fd[1] = pipes[0][1];
	}
}

void	msh_execute_pipeline_close(int pipes[2][2], int i, int last);

static void	execute_exit(t_ast *node, t_list **env_list,
		char **argv_arr, char **envp_arr)
{
	msh_execute_free(NULL, envp_arr);
	msh_execute_simple_cmd_builtin(node, env_list, argv_arr, 1);
}

static void	execute_simple_cmd(t_ast *node, t_list **env_list,
		int subshell_flag)
{
	char	**argv_arr;
	char	**envp_arr;
	int		status;

	argv_arr = NULL;
	envp_arr = NULL;
	if (msh_execute_simple_cmd_init(node, env_list, &envp_arr, &argv_arr)
		== ERROR)
		return (msh_execute_free_exit(EXIT_FAILURE, argv_arr, envp_arr));
	if (!argv_arr)
		return (msh_execute_free_exit(EXIT_SUCCESS, NULL, envp_arr));
	if (!ft_strcmp("exit", argv_arr[0]))
		return (execute_exit(node, env_list, argv_arr, envp_arr));
	status = 0;
	if (msh_builtins_get_builtin(argv_arr[0]))
		status = msh_execute_simple_cmd_builtin(node, env_list, argv_arr,
				subshell_flag);
	else
	{
		if (msh_execute_simple_cmd_redirs(node->children[1], NULL, env_list)
			== ERROR)
			return (msh_execute_free_exit(EXIT_FAILURE, argv_arr, envp_arr));
		status = msh_execute_simple_cmd_execute(argv_arr, envp_arr, env_list);
	}
	return (msh_execute_free_exit(status, argv_arr, envp_arr));
}

int		msh_execute_grouping(t_ast *node, t_list **env_list, int subshell_flag);

//Check leak before exit
static void	pipeline_execute(t_ast *node, int pipes[2][2], int i,
		t_list **env_list)
{
	int	fd[2];
	int	status;

	set_pipes(fd, pipes, i, (i == node->child_count - 1));
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
		return (msh_perror_exit(
				"msh_execute_pipeline_pipe_fork: pipeline_execute",
				"dup2",
				strerror(errno), EXIT_FAILURE));
	msh_execute_pipeline_close(pipes, -1, 0);
	if (!ft_strcmp(node->children[i]->type, "simple_command"))
		execute_simple_cmd(node->children[i], env_list, 1);
	else if (!ft_strcmp(node->children[i]->type, "grouping"))
	{
		status = msh_execute_grouping(node->children[i], env_list, 1);
		exit(status);
	}
	else
		msh_perror("debug: msh_execute_pipeline_pipe_fork: pipeline_execute",
			"Unknown AST node type", node->children[i]->type);
}

int	msh_execute_pipeline_pipe_fork(t_ast *node, int pipes[2][2], int i,
		t_list **env_list)
{
	int	pid;

	if (i != node->child_count - 1 && pipe(pipes[i % 2]) < 0)
		return (msh_perror_exit_int("msh_execute_pipeline_pipe_fork",
				"pipe(pipes[i % 2])", strerror(errno),
				EXIT_FAILURE));
	pid = fork();
	if (pid == -1)
	{
		msh_perror_exit("msh_execute_pipeline_pipe_fork",
			NULL, strerror(errno), EXIT_FAILURE);
		errno = 0;
		return (ERROR);
	}
	if (!pid)
		pipeline_execute(node, pipes, i, env_list);
	return (pid);
}
