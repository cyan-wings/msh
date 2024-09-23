/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirections_heredoc.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:35:39 by myeow             #+#    #+#             */
/*   Updated: 2024/09/23 01:31:15 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh_signal.h"
#include "get_next_line.h"

static void	heredoc_readline(const char *delim, char **heredoc_contents)
{
	char	*here_str;
	char	*read_str;

	signal(SIGINT, msh_signal_ctrl_c);
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
	*heredoc_contents = here_str;
}

static void	heredoc_gnl(const char *delim, char **heredoc_contents)
{
	char	*delim_nl;
	char	*here_str;
	char	*read_str;

	signal(SIGINT, msh_signal_ctrl_c);
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
	ft_memdel((void **)&delim_nl);
	*heredoc_contents = here_str;
}

void	msh_parse_cmd_redirections_heredoc(const char *delim,
			char **heredoc_contents)
{
	int		fd;

	if (!delim)
		msh_perror("debug", "msh_parse_cmd_redirections_heredoc",
			"delim is NULL");
	if (!heredoc_contents)
		msh_perror("debug", "msh_parse_cmd_redirections_heredoc",
			"heredoc_contents is NULL");
	fd = dup(STDIN_FILENO);
	if (fd == -1)
		msh_perror_exit("msh_parse_cmd_redirections", "redirection_heredoc",
			strerror(errno), EXIT_FAILURE);
	if (isatty(STDIN_FILENO))
		heredoc_readline(delim, heredoc_contents);
	else
		heredoc_gnl(delim, heredoc_contents);
	if (!*heredoc_contents)
		msh_perror("debug", "msh_parse_cmd_redirections: redirection_heredoc",
			"heredoc_contents is NULL");
	close(fd);
}
