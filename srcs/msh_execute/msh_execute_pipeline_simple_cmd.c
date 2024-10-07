/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline_simple_cmd.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:02:19 by myeow             #+#    #+#             */
/*   Updated: 2024/10/07 08:02:51 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

int    msh_execute_simple_cmd_init(t_ast *node, char ***argv_arr,
		t_list *env_list, char ***envp_arr);

// Method returns int to enhance readability and match msh_execute_free_exit return value.
int	msh_execute_pipeline_simple_cmd(t_ast *node, t_list **env_list,
		int subshell_flag)
{
	char	**argv_arr;
	char	**envp_arr;
	int		status;
	t_bif	*builtin_func;

	argv_arr = NULL;
	envp_arr = NULL;
	if (msh_execute_simple_cmd_init(node, &argv_arr, *env_list,
			&envp_arr) == ERROR)
		return (msh_execute_free_exit(EXIT_FAILURE, argv_arr, envp_arr));
	if (!argv_arr)
		return (msh_execute_free_exit(EXIT_SUCCESS, argv_arr, envp_arr));
	status = 0;
	builtin_func = msh_builtins_get_builtin(argv_arr[0]);
	if (builtin_func)
		status = msh_execute_simple_cmd_builtin(node, builtin_func, argv_arr, envp_arr);
	else
	{
		if (msh_execute_simple_cmd_redirs(node->children[1], NULL) == ERROR)
			return (msh_execute_free_exit(EXIT_FAILURE, argv_arr, envp_arr));
		status = msh_execute_simple_cmd_execute(argv_arr, envp_arr, env_list);
	}
	retur (msh_execute_free_exit(status, argv_arr, envp_arr));
}
