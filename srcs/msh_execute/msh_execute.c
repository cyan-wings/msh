/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:27:17 by myeow             #+#    #+#             */
/*   Updated: 2024/10/22 19:10:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

int	msh_execute_list(t_ast *node, t_list **env_list, int subshell_flag);
int	msh_execute_pipeline(t_ast *node, t_list **env_list, int subshell_flag);
int	msh_execute_grouping(t_ast *node, t_list **env_list, int subshell_flag);

static int	check_null_param(t_ast *node, t_list **env_list)
{
	int	flag;

	flag = 1;
	if (!node)
	{
		msh_perror("debug", "msh_execute", "node is NULL.");
		flag = 0;
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute", "env_list is NULL.");
		flag = 0;
	}
	return (flag);
}

int	msh_execute(t_ast *node, t_list **env_list, int subshell_flag)
{
	const char	*node_types[] = {
		"list", "pipeline", "grouping"};
	static int	(*exec_node_f[])(t_ast *node, t_list **env_list,
			int subshell_flag) = {msh_execute_list,
		msh_execute_pipeline, msh_execute_grouping};
	int			i;

	if (!check_null_param(node, env_list))
		return (ERROR);
	i = -1;
	while (++i < 3)
	{
		if (!ft_strcmp(node->type, node_types[i]))
		{
			msh_execute_exit_status_set(exec_node_f[i](node, env_list,
					subshell_flag));
			return (msh_execute_exit_status_get());
		}
	}
	return (msh_perror_int("debug: msh_execute", "Unknown AST node type",
			node->type));
}
