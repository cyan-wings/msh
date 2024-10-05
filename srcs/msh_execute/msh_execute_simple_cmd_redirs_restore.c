/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:14:55 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 21:40:42 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static void	msh_execute_simple_cmd_redirs_restore_helper(int fd_new,
			int fd_backup)
{
	if (fd_backup == -1 && close(fd_new) == -1)
		return (msh_perror_exit("msh_execute_simple_cmd_redirs_restore",
				"close(fd_new)", strerror(errno), EXIT_FAILURE));
	else
	{
		if (dup2(fd_backup, fd_new) == -1)
			return (msh_perror_exit("msh_execute_simple_cmd_redirs_restore",
					"dup2(fd_backup, fd_new)",
					strerror(errno), EXIT_FAILURE));
		if (close(fd_backup) == -1)
			return (msh_perror_exit("msh_execute_simple_cmd_redirs_restore",
					"close(fd_backup)", strerror(errno), EXIT_FAILURE));
	}
}

void	msh_execute_simple_cmd_redirs_restore(t_redir_st ***redir_st_arr)
{
	int	i;
	int	fd_new;
	int	fd_backup;

	if (!redir_st_arr)
		return (msh_perror("debug", "msh_execute_simple_cmd_redirs_restore",
				"redir_st_arr is NULL."));
	i = -1;
	while ((*redir_st_arr)[++i])
	{
		fd_new = (*redir_st_arr)[i]->fd_new;
		fd_backup = (*redir_st_arr)[i]->fd_backup;
		msh_execute_simple_cmd_redirs_restore_helper(fd_new, fd_backup);
	}
}