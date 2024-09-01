/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_traverse_nodes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:27:17 by myeow             #+#    #+#             */
/*   Updated: 2024/09/01 19:16:50 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem_utils.h"
#include "ft_string_utils.h"
#include "msh.h"
#include <stdio.h>
#include <sys/wait.h>

static int	msh_execute_list_op(t_ast *node, t_global *global)
{
	if (ft_strcmp(node->type, "list_op"))
		return (0);
	if (!ft_strcmp(node->value, "&&") && global->status != 0)
		return (1);
	if (!ft_strcmp(node->value, "||") && global->status == 0)
		return (1);
	return (0);
//TODO: what to do when its valid and when its not
}

void	msh_execute_pipeline(t_ast *node, t_list **env_list,
				t_global *global);

void	msh_execute_grouping(t_ast *node, t_list **env_list,
				t_global *global);

static int	execute_node(t_ast *node, t_list **env_list, t_global *global)
{
	int	res;

	res = 0;
	if (!ft_strcmp(node->type, "pipeline"))
		msh_execute_pipeline(node, env_list, global);
	else if (!ft_strcmp(node->type, "list_op"))
		res = msh_execute_list_op(node, global);
	else if (!ft_strcmp(node->type, "grouping"))
		msh_execute_grouping(node, env_list, global);
	else
		return (res);
	return (res);
}

int	msh_execute_traverse_nodes(t_ast *node, t_list **env_list,
		t_global *global)
{
	int	i;

	if (node == NULL)
		return (0);
	i = -1;
	while (++i < node->child_count)
	{
		if (msh_execute_traverse_nodes(node->children[i],
				env_list, global))
			return (1);
	}
	if (execute_node(node, env_list, global))
		return (1);
	return (0);
}
