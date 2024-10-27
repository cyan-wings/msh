/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:44 by myeow             #+#    #+#             */
/*   Updated: 2024/10/26 20:42:49 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

static int	check_null_param(t_list **token_ptr,
			t_ast **redirs_root_node, t_list *env_list)
{
	if (!token_ptr)
	{
		msh_perror("debug", "msh_parse_cmd_redirections",
			"token_ptr is NULL.");
		return (0);
	}
	if (!redirs_root_node)
	{
		msh_perror("debug", "msh_parse_cmd_redirections",
			"redirs_root_node is NULL.");
		return (0);
	}
	if (!env_list)
	{
		msh_perror("debug", "msh_parse_cmd_redirections",
			"env_list is NULL.");
		return (0);
	}
	return (1);
}

int	msh_parse_redirection_helper(t_token *curr, t_token *next,
				t_ast **redir_child_node);

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
int	msh_parse_cmd_redirection(t_list **token_ptr,
		t_ast **redirs_root_node, t_list *env_list)
{
	int		status;
	t_ast	*redir_child_node;

	if (!check_null_param(token_ptr, redirs_root_node, env_list))
		return (ERROR);
	status = 0;
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
	{
		if (!((*token_ptr)->next) || \
			((t_token *)(*token_ptr)->next->content)->type != WORD)
			return (ERROR);
		redir_child_node = NULL;
		status = msh_parse_redirection_helper(
				(t_token *)(*token_ptr)->content,
				(t_token *)(*token_ptr)->next->content, &redir_child_node);
		msh_parse_astadd_child(*redirs_root_node, redir_child_node);
		if (status)
			return (status);
		msh_tokenise_get_next_token(token_ptr);
		msh_tokenise_get_next_token(token_ptr);
	}
	return (status);
}
