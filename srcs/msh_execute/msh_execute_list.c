/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:40:57 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 21:41:23 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

int	msh_execute_list(t_ast *node, t_list **env_list, int subshell_flag)
{
	t_ast	*child;
	int		i;
	int		status;
	char	*op;

	child = NULL;
	i = 0;
	child = node->children[i];
	status = msh_execute(child, env_list, subshell_flag);
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
		status = msh_execute(child, env_list, subshell_flag);
	}
	return (status);
}
