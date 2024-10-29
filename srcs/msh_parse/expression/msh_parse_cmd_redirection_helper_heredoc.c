/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirection_helper_heredoc.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:35:39 by myeow             #+#    #+#             */
/*   Updated: 2024/10/26 20:44:17 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh_signal.h"
#include "msh_execute.h"
#include "get_next_line.h"

static void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (close(STDIN_FILENO) == -1)
			return (msh_perror_exit(",msh_parse_cmd_redirections_heredoc",
					"signal_heredoc", strerror(errno), EXIT_FAILURE));
		ft_putchar_fd('\n', STDERR_FILENO);
		msh_execute_exit_status_set(EXIT_FAILURE);
	}
}

static void	heredoc_readline(const char *delim, char **heredoc_contents)
{
	char	*here_str;
	char	*read_str;

	signal(SIGINT, signal_heredoc);
	here_str = NULL;
	read_str = NULL;
	read_str = readline("> ");
	while (read_str && ft_strcmp(read_str, delim))
	{
		ft_strvappend(&here_str, read_str, "\n", NULL);
		ft_memdel((void **)&read_str);
		if (!here_str)
			return (msh_perror_exit("msh_parse_cmd_redirections_heredoc",
					"heredoc_readline: here_str", "malloc fail.",
					EXIT_FAILURE));
		read_str = readline("> ");
	}
	ft_memdel((void **)&read_str);
	*heredoc_contents = here_str;
}

static void	heredoc_gnl(const char *delim, char **heredoc_contents)
{
	char	*delim_nl;
	char	*here_str;
	char	*read_str;

	signal(SIGINT, signal_heredoc);
	delim_nl = NULL;
	ft_strvappend(&delim_nl, delim, "\n", NULL);
	if (!delim_nl)
		msh_perror_exit("msh_parse_cmd_redirections", "heredoc_gnl: delim_nl",
			"malloc fail.", EXIT_FAILURE);
	here_str = NULL;
	read_str = NULL;
	read_str = get_next_line(STDIN_FILENO);
	while (read_str && ft_strcmp(read_str, delim_nl))
	{
		ft_strappend(&here_str, read_str);
		ft_memdel((void **)&read_str);
		if (!here_str)
			msh_perror_exit("msh_parse_cmd_redirections",
				"heredoc_gnl: here_str", "malloc fail.", EXIT_FAILURE);
		read_str = get_next_line(STDIN_FILENO);
	}
	ft_memdel((void **)&read_str);
	ft_memdel((void **)&delim_nl);
	*heredoc_contents = here_str;
}

static int	sigint_heredoc(int fd, char **heredoc_contents)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (msh_perror_exit_int("msh_parse_cmd_redirections_heredoc",
				NULL, strerror(errno), EXIT_FAILURE));
	close(fd);
	ft_memdel((void **)heredoc_contents);
	return (HEREDOC_SIGINT_ERROR);
}

/*
 * Function that prompts the heredoc input and processes it.
 * 
 * 		(1) Here document (i.e., operator is <<)
 * 		(2) Rest of the operators (i.e., <, >, >>)
 * 
 * Notes:
 * 		(1) When interrupted with SIGINT, the file is closed in 
 * 			the signal_heredoc(int sig) function, causing 
 * 			errno to be EBADF.
 * 		(2) Heredoc contents can be NULL when limiter is passed
 * 			immediately in the first prompt. A single memory
 * 			block is allocated to denote an empty string.
 */
int	msh_parse_cmd_redirection_helper_heredoc(char *delim,
			char **heredoc_contents)
{
	int		fd;

	if (!heredoc_contents)
		msh_perror("debug", "msh_parse_cmd_redirections_heredoc",
			"heredoc_contents is NULL.");
	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (msh_perror_exit_int("msh_parse_cmd_redirections", NULL,
				strerror(errno), EXIT_FAILURE));
	if (isatty(STDIN_FILENO))
		heredoc_readline(delim, heredoc_contents);
	else
		heredoc_gnl(delim, heredoc_contents);
	ft_memdel((void **)&delim);
	if (errno == EBADF)
		return (sigint_heredoc(fd, heredoc_contents));
	if (!*heredoc_contents)
		*heredoc_contents = msh_utils_memalloc(1,
				"msh_parse_cmd_redirections_heredoc", "memalloc");
	if (close(fd) == -1)
		return (msh_perror_exit_int(",msh_parse_cmd_redirections_heredoc",
				NULL, strerror(errno), EXIT_FAILURE));
	return (0);
}
