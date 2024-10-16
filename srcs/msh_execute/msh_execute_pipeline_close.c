/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_pipeline_close.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 08:01:04 by myeow             #+#    #+#             */
/*   Updated: 2024/10/07 08:01:49 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static void	close_end(int *pipe_end)
{
	if (*pipe_end == -1)
		return ;
	if (close(*pipe_end) == -1)
		return (msh_perror_exit("msh_execute_pipeline_close",
				"close_pipe", strerror(errno), EXIT_FAILURE));
	*pipe_end = -1;
}

void	msh_execute_pipeline_close(int pipes[2][2], int i, int last)
{
	if (!i)
		close_end((int *)&(pipes[0][1]));
	else if (last)
		close_end((int *)&(pipes[(i + 1) % 2][0]));
	else if (i == -1)
	{
		close_end((int *)&(pipes[0][0]));
		close_end((int *)&(pipes[0][1]));
		close_end((int *)&(pipes[1][0]));
		close_end((int *)&(pipes[1][1]));
	}
	else if (i % 2 == 1)
	{
		close_end((int *)&(pipes[0][0]));
		close_end((int *)&(pipes[1][1]));
	}
	else if (i % 2 == 0)
	{
		close_end((int *)&(pipes[1][0]));
		close_end((int *)&(pipes[0][1]));
	}
}
