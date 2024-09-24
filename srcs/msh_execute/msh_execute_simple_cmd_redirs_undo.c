#include "msh_execute.h"
static t_list	*redir_st_create(int fd_new, int fd_backup)
{
	t_redir_st	*redir_st;

	redir_st = (t_redir_st *)malloc(sizeof(t_redir_st));
	if (!redir_st)
    {
        msh_perror_exit("msh_execute_simple_cmd_redirs_st", "redir_st_create",
            "malloc fail.", EXIT_FAILURE);
		return (NULL);
    }
	redir_st->fd_new = fd_new;
	redir_st->fd_backup = fd_backup;
	return (ft_lstnew(redir_st));
}

int	redir_st_add(t_list **redir_st_list, int fd)
{
	t_list	*curr;
    t_list	*head;
	int		tmp;

	curr = *redir_st_list;
	while (curr)
	{
		if (((t_redir_st *)(curr->content))->fd_new == fd)
			return (0);
		curr = curr->next;
	}
	tmp = dup(fd);
	if (tmp == -1 && errno != EBADF)
		return (msh_perror_exit_int("msh_execute_simple_cmd_redirs_st_redir_st_add",
                "dup(fd)", strerror(errno), EXIT_FAILURE));
	else
		ft_lstadd_back(redir_st_list, redir_st_create(fd, tmp));
	return (0);
}

void	msh_execute_simple_cmd_redirs_st(t_list **redir_st_list)
{
	t_list	*curr;
	int		fd_new;
	int		fd_backup;

	curr = *redir_st_list;
	while (curr)
	{
		fd_new = ((t_redir_st *)(curr->content))->fd_new;
		fd_backup = ((t_redir_st *)(curr->content))->fd_backup;
		if (fd_backup == -1)
			close(fd_backup);
		else if (fd_backup != -1)
		{
			if (dup2(fd_backup, fd_new) == -1)
				return (msh_perror_exit("msh_execute_simple_cmd_redirs_undo",
                        "dup2(fd_backup, fd_new)", strerror(errno), EXIT_FAILURE));
			close(fd_backup);
		}
		curr = curr->next;
	}
	ft_lstclear(redir_st_list, free);
}