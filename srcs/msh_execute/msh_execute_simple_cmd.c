/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:14:55 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 08:19:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh.h"

static int	check_param(t_ast *node, t_list **env_list)
{
	int	flag;

	flag = 1;
	if (!node)
	{
		msh_perror("debug", "msh_execute_simple_cmd", "node is NULL.");
		flag = 0;
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute_simple_cmd", "env_list is NULL.");
		flag = 0;
	}
	if (node && !node->child_count)
	{
		msh_perror("debug", "msh_execute_simple_cmd",
			"No child nodes in simple_command.");
		flag = 0;
	}
	if (node && ft_strcmp(node->type, "msh_execute_simple_cmd"))
	{
		msh_perror("debug", "msh_execute_simple_cmd", "type is incorrect.");
		flag = 0;
	}
	return (flag);
}

int		msh_execute_simple_cmd_init(t_ast *node, char ***argv_arr,
			t_list *env_list, char ***envp_arr);

void	msh_execute_free(char **argv_arr, char **envp_arr);

int		msh_execute_simple_cmd_builtin(t_ast *node, t_list **env_list,
			char **argv_arr, int subshell_flag);

int		msh_execute_simple_cmd_redirs(t_ast *redirs_node,
			t_redir_st ***redir_st_arr);

void	msh_execute_free_exit(int status, char **argv_arr, char **envp_arr);

int		msh_execute_simple_cmd_execute(char **argv_arr, char **envp_arr,
			t_list **env_list);

int		msh_execute_wait_pid(int prev_pid, char *name);

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
			msh_execute_free_exit(EXIT_FAILURE, argv_arr, envp_arr);
		status = msh_execute_simple_cmd_execute(argv_arr, envp_arr, env_list);
		msh_execute_free_exit(status, argv_arr, envp_arr);
	}
	status = msh_execute_wait_pid(pid, argv_arr[0]);
	return (status);
}

int	msh_execute_simple_cmd(t_ast *node, t_list **env_list, int subshell_flag)
{
	char	**argv_arr;
	char	**envp_arr;
	int		status;

	if (!check_param(node, env_list))
		return (ERROR);
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
	if (msh_builtins_get_builtin(argv_arr[0]))
	{
		msh_execute_free(NULL, envp_arr);
		return (msh_execute_simple_cmd_builtin(node, env_list,
				argv_arr, subshell_flag));
	}
	status = msh_execute_simple_cmd_helper(node, env_list, argv_arr, envp_arr);
	msh_execute_free(argv_arr, envp_arr);
	return (status);
}
