/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:44 by myeow             #+#    #+#             */
/*   Updated: 2024/09/22 15:40:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "msh.h"

void	msh_expansion_quotes(char **strptr);

int		msh_parse_cmd_redirections_heredoc(const char *delim,
			char **heredoc_contents);

static int	redirection(t_token *curr, t_token *next,
					t_ast **redir_child_node)
{
	char	*redir_op;
	t_ast	*redir_file;
	int		status;
	char	*heredoc_contents;

	redir_op = curr->value;
	redir_file = NULL;
	status = 0;
	if (!ft_strcmp(redir_op, "<<"))
	{
		msh_expansion_quotes(&next->value);
		heredoc_contents = NULL;
		status = msh_parse_cmd_redirections_heredoc(next->value,
				&heredoc_contents);
		redir_file = msh_parse_astnew("heredoc", heredoc_contents);
		ft_memdel((void **)&heredoc_contents);
		signal(SIGINT, msh_signal_ctrl_c);
	}
	else
		redir_file = msh_parse_astnew("file", next->value);
	*redir_child_node = msh_parse_astnew("redirection", redir_op);
	msh_parse_astadd_child(*redir_child_node, redir_file);
	return (status);
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
	int		status;

	if (!token_ptr)
		msh_perror("debug", "msh_parse_cmd_redirections", "token_ptr is NULL.");
	if (!redirs_root_node)
		msh_perror("debug", "msh_parse_cmd_redirections",
			"redirs_root_node is NULL.");
	redir_child_node = NULL;
	status = 0;
	while (!status && *token_ptr
		&& ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
	{
		if (!((*token_ptr)->next) || \
			((t_token *)(*token_ptr)->next->content)->type != WORD)
			return (ERROR);
		status = redirection((t_token *)(*token_ptr)->content, \
				(t_token *)(*token_ptr)->next->content, &redir_child_node);
		msh_parse_astadd_child(*redirs_root_node, redir_child_node);
		msh_tokenise_get_next_token(token_ptr);
		msh_tokenise_get_next_token(token_ptr);
	}
	return (status);
}
