#include "msh_execute.h"

static void	free_redir_st_arr(t_redir_st **redir_st_arr)
{
	int	i;

	i = -1;
	if (redir_st_arr)
	{
		while (redir_st_arr[++i])
			ft_memdel((void **) &redir_st_arr[i]);
		ft_memdel((void **) &redir_st_arr);
	}
}

void	msh_execute_simple_cmd_redirs_restore(t_redir_st **redir_st_arr)
{
	int	i;
	int	fd_new;
	int	fd_backup;

	i = -1;
	while (redir_st_arr[++i])
	{
		fd_new = redir_st_arr[i]->fd_new;
		fd_backup = redir_st_arr[i]->fd_backup;
		if (fd_backup == -1)
			close(fd_backup);
		else if (fd_backup != -1)
		{
			if (dup2(fd_backup, fd_new) == -1)
				return (msh_perror_exit("msh_execute_simple_cmd_redirs_restore",
                        "dup2(fd_backup, fd_new)", strerror(errno), EXIT_FAILURE));
			close(fd_backup);
		}
	}
	free_redir_st_arr(redir_st_arr);
}