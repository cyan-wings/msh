/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirections.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:44 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:53:56 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

static t_ast	*redirection(t_token *curr, t_token *next)
{
	char	*redir_op;
	t_ast	*redir_file;
	t_ast	*redir_node;

	redir_op = curr->value;
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

	redir_child_node = 0;
	while (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
	{
		if (!((*token_ptr)->next) || \
			((t_token *)(*token_ptr)->next->content)->type != WORD)
		{
			msh_parse_astfree(&redir_child_node);
			return (0);
		}
		redir_child_node = redirection((t_token *)(*token_ptr)->content, \
				(t_token *)(*token_ptr)->next->content);
		msh_parse_astadd_child(*redirs_root_node, redir_child_node);
		msh_tokenise_get_next_token(token_ptr);
		msh_tokenise_get_next_token(token_ptr);
	}
	return (1);
}
