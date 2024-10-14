/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_builtin.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:31:32 by myeow             #+#    #+#             */
/*   Updated: 2024/10/11 08:17:50 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static int	check_null_param(t_ast *node, t_list **env_list,
				char **argv_arr)
{
	if (!node)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
			"node is NULL.");
		return (0);
	}
	if (!argv_arr)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
			"argv_arr is NULL.");
		return (0);
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init",
			"env_list is NULL.");
		return (0);
	}
	return (1);
}

int	msh_execute_simple_cmd_builtin(t_ast *node, t_list **env_list,
		char **argv_arr, int subshell_flag)
{
	int			status;
	t_redir_st	**redir_st_arr;
	t_bif		*builtin_func;

	if (!check_null_param(node, env_list, argv_arr))
		return (ERROR);
	status = ERROR;
	redir_st_arr = NULL;
	builtin_func = msh_builtins_get_builtin(argv_arr[0]);
	if (builtin_func)
	{
		status = msh_execute_simple_cmd_redirs(node->children[1],
				&redir_st_arr);
		if (status != ERROR)
			status = (*builtin_func)(node->children[0]->child_count,
					argv_arr, env_list, subshell_flag);
		if (redir_st_arr)
			msh_execute_simple_cmd_redirs_restore(&redir_st_arr);
	}
	return (status);
}
