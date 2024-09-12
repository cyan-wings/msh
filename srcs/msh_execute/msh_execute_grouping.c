/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_grouping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:24:31 by myeow             #+#    #+#             */
/*   Updated: 2024/09/07 00:36:04 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

//int	msh_execute_traverse_nodes(t_ast *node, t_list **env_list,
//		t_global *global);

int	msh_execute_grouping(t_ast *node, t_list **env_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		status = msh_execute(node->children[0], env_list);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid failed in subshell");
		if (WIFEXITED(status))
			WEXITSTATUS(status);
	}
	return ( status );
}

