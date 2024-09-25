#include "msh_execute.h"

static t_redir_type	get_redir_type(char *op)
{
	if (!op)
		msh_perror("debug", "msh_execute_simple_cmd_redirs", "op is NULL");
	if (*op == '>')
	{
		++op;
		if (!*op)
			return (REDIR_OUT);
		else if (*op == '>')
			return (REDIR_APP);
	}
	else if (*op == '<')
	{
		++op;
		if (!*op)
			return (REDIR_IN);
		else if (*op == '<')
			return (REDIR_HERE);
	}
	msh_perror("debug", "msh_execute_simple_cmd_redirs", "Unknown redir op");
	return (ERROR);
}

static int	get_redir_in(char *file, int type)
{
	int	fd[2];

	if (type == REDIR_HERE)
	{
		if (pipe(fd) == -1)
			return (msh_perror_exit_int("msh_execute_simple_cmd_redirs",
					"redir_open_file: pipe", strerror(errno), EXIT_FAILURE));
		write(fd[1], file, ft_strlen(file));
		close(fd[1]);
	}
	else if (type == REDIR_IN)
		fd[0] = open(file, O_RDONLY, 0);
	else if (type == REDIR_OUT)
		fd[0] = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == REDIR_APP)
		fd[0] = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[0] == -1)
		return (msh_perror_exit_int("msh_execute_simple_cmd_redirs",
				"redir_open_file: open", strerror(errno), EXIT_FAILURE));
	return (fd[0]);
}

static int	get_redir_out(t_redir_type redir_type)
{
	if (redir_type == REDIR_OUT || redir_type == REDIR_APP)
		return (STDOUT_FILENO);
	if (redir_type == REDIR_IN || redir_type == REDIR_HERE)
		return (STDIN_FILENO);
	return (msh_perror_exit_int("debug", "msh_execute_simple_cmd_redirs",
			"redir_fd", EXIT_FAILURE));
}

void	add_redir_st(t_redir_st **redir_st_arr, int fd)
{
    int         i;
	int		    tmp;
    t_redir_st  *redir_st_elem;

    i = -1;
	while (redir_st_arr[++i])
		if (redir_st_arr[i]->fd_new == fd)
			return ;
	tmp = dup(fd);
	if (tmp == -1 && errno != EBADF)
		return (msh_perror_exit("msh_execute_simple_cmd_redirs_st_redir_st_add",
                "dup(fd)", strerror(errno), EXIT_FAILURE));
	else
    {
        redir_st_elem = (t_redir_st *)ft_memalloc(sizeof(t_redir_st));
	    if (!redir_st_elem)
            return (msh_perror_exit("msh_execute_simple_cmd_redirs_st", "redir_st_create",
                "malloc fail.", EXIT_FAILURE));
	    redir_st_elem->fd_new = fd;
	    redir_st_elem->fd_backup = tmp;
        redir_st_arr[i] = redir_st_elem;
    }
}

void    msh_execute_simple_cmd_redirs_process(char *op, char *file,
            t_redir_st **redir_st_arr)
{
	int	redir_type;
	int	fd[2];

	redir_type = get_redir_type(op);
	fd[0] = get_redir_in(file, redir_type);
	fd[1] = get_redir_out(redir_type);
	add_redir_st(redir_st_arr, fd[1]);
	if (dup2(fd[0], fd[1]) == -1)
		return (msh_perror_exit("msh_execute_simple_cmd_redirs",
				"redir_process: dup2(fd[0], fd[1])",
				strerror(errno), EXIT_FAILURE));
	if (fd[1] != -1)
		close(fd[1]);
}