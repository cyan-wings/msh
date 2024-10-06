/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:14:55 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 21:40:42 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

void msh_execute_simple_cmd_get_envp_arr(t_list *env_list, char ***envp_arr);

int	msh_execute_simple_cmd_helper(t_ast *node, t_list **env_list,
		char **argv_arr, char **envp_arr)
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
		if (msh_execute_simple_cmd_redirs(node->children[1], NULL) == ERROR)
			return (msh_execute_free_exit(EXIT_FAILURE, argv_arr, envp_arr));
		status = msh_execute_simple_cmd_execute(argv_arr, envp_arr, env_list);
		return (msh_execute_free_exit(status, argv_arr, envp_arr));
	}
	status = msh_execute_wait_pid(pid, argv_arr[0]);
	return (status);
}

int	msh_execute_simple_cmd(t_ast *node, t_list **env_list)
{
	char	**argv_arr;
	char	**envp_arr;
	t_bif	*builtin_func;
	int		status;

	argv_arr = NULL;
	envp_arr = NULL;
	if (msh_execute_simple_cmd_init(node, &argv_arr, *env_list,
			&envp_arr) == ERROR)
	{
		msh_execute_free(argv_arr, envp_arr);
		return (EXIT_FAILURE);
	}
	if (!argv_arr)
	{
		msh_execute_free(argv_arr, envp_arr);
		return (EXIT_SUCCESS);
	}
	builtin_func = msh_builtins_get_builtin(argv_arr[0]);
	if (builtin_func)
		return (msh_execute_simple_cmd_builtin(node, builtin_func, argv_arr, envp_arr));
	status = msh_exeucte_simple_cmd_helper(node, env_list, argv_arr, envp_arr);
	msh_execute_free(argv_arr, envp_arr);
	return (status);
}