#include "msh_execute.h"

static void	close_pipe(int pipe_end)
{
	if (pipe_end == -1)
		return ;
    if (close(pipe_end) == -1)
        return (msh_perror_exit("msh_execute_pipeline_close",
                "close_pipe", strerror(errno), EXIT_FAILURE));
}

//double check
void	msh_execute_pipeline_close(int pipes[2][2], int i, int last)
{
	if (!i)
		close_pipe(pipes[0][1]);
	else if (last)
		close_pipe(pipes[(i + 1) % 2][0]);
    else if (i == -1)
	{
		close_pipe(pipes[0][0]);
		close_pipe(pipes[0][1]);
		close_pipe(pipes[1][0]);
		close_pipe(pipes[1][1]);
	}
	else if (i % 2 == 1)
	{
		close_pipe(pipes[0][0]);
		close_pipe(pipes[1][1]);
	}
    else
	{
		close_pipe(pipes[1][0]);
		close_pipe(pipes[0][1]);
	}
}