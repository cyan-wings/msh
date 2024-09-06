/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_grouping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:24:31 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 20:26:35 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_execute_traverse_nodes(t_ast *node, t_list **env_list,
		t_global *global);

void	msh_execute_grouping(t_ast *node, t_list **env_list,
		t_global *global)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		msh_execute_traverse_nodes(node->children[0], env_list, global);
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid failed in subshell");
		if (WIFEXITED(status))
			global->status = WEXITSTATUS(status);
	}
}
