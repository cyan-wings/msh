/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_grouping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:24:31 by myeow             #+#    #+#             */
/*   Updated: 2024/09/30 13:34:54 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static int	check_param(t_ast *node, t_list **env_list)
{
	int	flag;

	flag = 1;
	if (!node)
	{
		msh_perror("debug", "msh_execute_grouping", "node is NULL.");
		flag = 0;
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_execute_grouping", "env_list is NULL.");
		flag = 0;
	}
	if (node && ft_strcmp(node->type, "grouping"))
	{
		msh_perror("debug", "msh_execute_grouping", "node is not grouping");
		flag = 0;
	}
	return (flag);
}

int	msh_execute_grouping(t_ast *node, t_list **env_list,
		int subshell_flag __attribute((unused)))
{
	pid_t	pid;
	int		status;

	if (!check_param(node, env_list))
		return (ERROR);
	pid = fork();
	if (pid == -1)
	{
		msh_perror_exit("msh_execute_grouping", NULL, strerror(errno),
			EXIT_FAILURE);
		errno = 0;
		return (ERROR);
	}
	if (pid == 0)
	{
		status = msh_execute(node->children[0], env_list, 1);
		exit(status);
	}
	return (msh_execute_wait_pid(pid, NULL));
}
