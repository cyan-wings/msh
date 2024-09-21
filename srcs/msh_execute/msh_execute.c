/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:27:17 by myeow             #+#    #+#             */
/*   Updated: 2024/09/17 15:35:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execution.h"

static int	msh_execute_list(t_ast *node, t_list **env_list)
{
	t_ast	*child;
	int		i;
	int		status;
	char	*op;

	child = NULL;
	i = 0;
	child = node->children[i];
	status = msh_execute(child, env_list);
	while (++i < node->child_count)
	{
		child = node->children[i];
		op = (char *)child->value;
		if ((!ft_strcmp(op, "&&") && status)
			|| (!ft_strcmp(op, "||") && !status))
		{
			++i;
			continue ;
		}
		child = node->children[++i];
		status = msh_execute(child, env_list);
	}
	return (status);
}

// static int	msh_execute_grouping(t_ast *node, t_list **env_list)
// {
// 	return (msh_execute(node->children[0], env_list));
// }
//int	msh_execute_grouping(t_ast *node, t_list **env_list, int flag_fork);
int	msh_execute_grouping(t_ast *node, t_list **env_list);
int	msh_execute_simple_cmd(t_ast *node, t_list **env_list);

int	msh_execute_pipeline(t_ast *node, t_list **env_list);

int	msh_execute(t_ast *node, t_list **env_list)
{
	const char	*types[] = {
		"list", "pipeline", "grouping", "simple_command"};
	static int	(*exec_node_f[])(t_ast *node, t_list **env_list) = {
		msh_execute_list, msh_execute_pipeline, msh_execute_grouping,
		msh_execute_simple_cmd};
	int			i;

	if (!node)
		return (-1);
	i = -1;
	while (++i < 4)
		if (!ft_strcmp(node->type, types[i]))
			return (exec_node_f[i](node, env_list));
	printf("Unknown AST node type: %s\n", node->type);
	return (-1);
}
