/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:14:55 by myeow             #+#    #+#             */
/*   Updated: 2024/10/30 17:22:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

static int	ret_func(char **argv_arr, char **envp_arr, int status)
{
	msh_execute_free(argv_arr, envp_arr);
	return (status);
}

int	msh_execute_simple_cmd_helper(t_ast *node, t_list **env_list,
		char **envp_arr, char **argv_arr)
{
	int		status;
	int		pid;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (msh_perror_exit_int("msh_execute_pipeline",
				"pipeline_pipe_fork: pid", strerror(errno), EXIT_FAILURE));
	if (!pid)
	{
		if (msh_execute_simple_cmd_redirs(node->children[1], NULL, env_list)
			== ERROR)
			msh_execute_free_exit(EXIT_FAILURE, argv_arr, envp_arr);
		status = msh_execute_simple_cmd_execute(argv_arr, envp_arr, env_list);
		msh_execute_free_exit(status, argv_arr, envp_arr);
	}
	status = msh_execute_wait_pid(pid, argv_arr[0]);
	return (ret_func(argv_arr, envp_arr, status));
}

/*
 * 	Process:
 * 		(1) Init: Create the envp and argv array
 * 			and TEST perform redirections.
 * 		(2) When no argv array, means the command only has redirs.
 * 		(3) Check if the executable matches any builtins and runs it
 * 			if there is a match.
 * 		(4) Runs the fork and execve.
 */
int	msh_execute_simple_cmd(t_ast *node, t_list **env_list, int subshell_flag)
{
	char	**argv_arr;
	char	**envp_arr;
	int		status;

	argv_arr = NULL;
	envp_arr = NULL;
	if (msh_execute_simple_cmd_init(node, env_list, &envp_arr, &argv_arr)
		== ERROR)
		return (ret_func(argv_arr, envp_arr, ERROR));
	if (!argv_arr)
		return (ret_func(NULL, envp_arr, EXIT_SUCCESS));
	if (!ft_strcmp("exit", argv_arr[0]))
	{
		msh_execute_free(NULL, envp_arr);
		return (msh_execute_simple_cmd_builtin(node, env_list, argv_arr,
				subshell_flag));
	}
	status = 0;
	if (msh_builtins_get_builtin(argv_arr[0]))
	{
		status = msh_execute_simple_cmd_builtin(node, env_list, argv_arr,
				subshell_flag);
		return (ret_func(argv_arr, envp_arr, status));
	}
	return (msh_execute_simple_cmd_helper(node, env_list, envp_arr, argv_arr));
}
