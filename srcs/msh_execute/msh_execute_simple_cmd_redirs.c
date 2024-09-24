/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_redirs.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:42:13 by myeow             #+#    #+#             */
/*   Updated: 2024/09/24 21:43:30 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "msh_execute.h"

static t_redir_type	get_redir_type(char *op)
{
	int	i;

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

static int	redir_open_file(char *file, int type)
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

static int	redir_fd(t_redir_type redir_type)
{
	if (redir_type == REDIR_OUT || redir_type == REDIR_APP)
		return (STDOUT_FILENO);
	if (redir_type == REDIR_IN || redir_type == REDIR_HERE)
		return (STDIN_FILENO);
	return (msh_perror_exit_int("debug", "msh_execute_simple_cmd_redirs",
			"redir_fd", EXIT_FAILURE));
}

static int	redir_process(char *op, char *file, t_list **l_undo)
{
	int	redir_type;
	int	fd[2];

	redir_type = get_redir_type(op);
	fd[0] = redir_open_file(file, redir_type);
	fd[1] = redir_fd(redir_type);


	if (l_undo && redir_undo_add_fd(l_undo, fd[1]) == ERROR)
		status = ERROR;
	if (status != ERROR && dup2(fd[0], fd[1]) == -1)
		status = print_error_errno(SHELL_NAME, redir, NULL);

	if (fd[1] != -1)
		close(fd[1]);
	return (status);
}

void	msh_execute_util_dup2(int oldfd, int newfd);

/*
 * TODO:
 * 	Flag errors when file does not exist based on bash behavior.
 */
void	msh_execute_simple_cmd_redirs(t_ast *node)
{
	int		i;
	int		in;
	int		out;
	t_ast	*current;

	i = -1;
	in = -69;
	out = -69;
	while (++i < node->child_count)
	{
		current = node->children[i];
		redir_process(current->value, current->children[0]->value, NULL);
	}
	//if (in != -69)
		//msh_execute_util_dup2(in, STDIN_FILENO);
	//if (out != -69)
		//msh_execute_util_dup2(out, STDOUT_FILENO);
}
