/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:44 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:54:19 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"

static void	heredoc_readline(const char *delim, char **heredoc_contents)
{
	char	*here_str;
	char	*read_str;
	char	*read_str_nl;
	char	*temp;

	signal(SIGINT, msh_signal_ctrl_c);
	here_str = NULL;
	here_str = ft_strdup("");
	if (!here_str)
		msh_perror_exit("msh_parse_cmd_redirections", "heredoc_readline: here_str", "malloc fail.", EXIT_FAILURE);
	read_str = NULL;
	read_str = readline("> ");
	while (read_str && ft_strcmp(read_str, delim))
	{
		read_str_nl = NULL;
		read_str_nl = ft_strjoin(read_str, "\n");
		ft_memdel((void **)&read_str);
		if (!read_str_nl)
			msh_perror_exit("msh_parse_cmd_redirections", "heredoc_readline: read_str_nl", "malloc fail.", EXIT_FAILURE);
		temp = NULL;
		temp = ft_strjoin(here_str, read_str_nl);
		ft_memdel((void **)&here_str);
		ft_memdel((void **)&read_str_nl);
		if (!temp)
			msh_perror_exit("msh_parse_cmd_redirections", "heredoc_readline: temp", "malloc fail.", EXIT_FAILURE);
		here_str = temp;
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
	char	*temp;

	signal(SIGINT, msh_signal_ctrl_c);
	delim_nl = ft_strjoin(delim, "\n");
	if (!delim_nl)
		msh_perror_exit("msh_parse_cmd_redirections", "heredoc_gnl: delim_nl", "malloc fail.", EXIT_FAILURE);
	here_str = NULL;
	here_str = ft_strdup("");
	if (!here_str)
		msh_perror_exit("msh_parse_cmd_redirections", "heredoc_gnl: here_str", "malloc fail.", EXIT_FAILURE);
	read_str = NULL;
	read_str = get_next_line(STDIN_FILENO);
	while (read_str && ft_strcmp(read_str, delim_nl))
	{
		temp = NULL;
		temp = ft_strjoin(here_str, read_str);
		if (!temp)
			msh_perror_exit("msh_parse_cmd_redirections", "heredoc_readline: temp", "malloc fail.", EXIT_FAILURE);
		here_str = temp;
		ft_memdel((void **)&read_str);
		read_str = get_next_line(STDIN_FILENO);
	}
	ft_memdel((void **)&delim_nl);
	*heredoc_contents = here_str;
}

/*
 * TODO: delims have to do quote expansion.
 */
static void	redirection_heredoc(const char *delim, char **heredoc_contents)
{
	int		fd;

	fd = dup(STDIN_FILENO);
	if (fd == -1)
		msh_perror_exit("msh_parse_cmd_redirections", "redirection_heredoc", strerror(errno), EXIT_FAILURE);
	if (isatty(STDIN_FILENO))
		heredoc_readline(delim, heredoc_contents);
	else
		heredoc_gnl(delim, heredoc_contents);
	if (!*heredoc_contents)
		msh_perror("debug", "msh_parse_cmd_redirections: redirection_heredoc", "heredoc_contents is NULL");
	close(fd);
}

void	msh_expansion_quotes(char **strptr);

static t_ast	*redirection(t_token *curr, t_token *next)
{
	char	*redir_op;
	t_ast	*redir_file;
	char	*heredoc_contents;
	t_ast	*redir_node;

	redir_op = curr->value;
	if (!ft_strcmp(redir_op, "<<"))
	{
		msh_expansion_quotes(&next->value);
		heredoc_contents = NULL;
		redirection_heredoc(next->value, &heredoc_contents);
		redir_file = msh_parse_astnew("heredoc", heredoc_contents);
	}
	else
		redir_file = msh_parse_astnew("file", next->value);
	redir_node = msh_parse_astnew("redirection", redir_op);
	msh_parse_astadd_child(redir_node, redir_file);
	return (redir_node);
}

/*
 * When this function enters current token is assumed to be of REDIR_OP type.
 * Hence, no check is needed.
 * Validation is needed for next token to be a WORD, otherwise parsing fails.
 *
 * Return:	0 if parsing grammar is erronous. 1 if successful.
 *
 * Notes:	Freeing due to error is done outside this function
 * 			on the redirections node.
 */
int	msh_parse_cmd_redirections(t_list **token_ptr,
		t_ast **redirs_root_node)
{
	t_ast	*redir_child_node;

	if (!token_ptr)
		msh_perror("debug", "msh_parse_cmd_redirections", "token_ptr is NULL.");
	if (!redirs_root_node)
		msh_perror("debug", "msh_parse_cmd_redirections", "redirs_root_node is NULL.");
	redir_child_node = NULL;
	while (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
	{
		if (!((*token_ptr)->next) || \
			((t_token *)(*token_ptr)->next->content)->type != WORD)
			return (0);
		redir_child_node = redirection((t_token *)(*token_ptr)->content, \
				(t_token *)(*token_ptr)->next->content);
		msh_parse_astadd_child(*redirs_root_node, redir_child_node);
		msh_tokenise_get_next_token(token_ptr);
		msh_tokenise_get_next_token(token_ptr);
	}
	return (1);
}
