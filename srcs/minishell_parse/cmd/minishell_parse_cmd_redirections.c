/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_cmd_redirections.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:48:03 by myeow             #+#    #+#             */
/*   Updated: 2024/07/04 17:42:06 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*redirection(t_token *curr, t_token *next)
{
	char	*redir_op;
	t_ast	*redir_file;
	t_ast	*redir_node;

	redir_op = curr->value;
	redir_file = minishell_parse_astnew("file", next->value);
	redir_node = minishell_parse_astnew("redirection", redir_op);
	minishell_parse_astadd_child(redir_node, redir_file);
	return (redir_node);
}

void	minishell_parse_cmd_redirections(t_list **token_ptr,
		t_ast **redirs_root_node)
{
	t_token	*token_curr;
	t_token	*token_next;
	t_ast	*redir_child_node;

	token_curr = (t_token *)(*token_ptr)->content;
	token_next = (t_token *)(*token_ptr)->next->content;
	while (*token_ptr && token_curr->type == REDIR_OP && \
			(*token_ptr)->next && token_next->type == WORD)
	{
		redir_child_node = redirection(token_curr, token_next);
		minishell_parse_astadd_child(*redirs_root_node, redir_child_node);
		minishell_tokenise_get_next_token(token_ptr);
		minishell_tokenise_get_next_token(token_ptr);
		if (*token_ptr && (*token_ptr)->next)
		{
			token_curr = (t_token *)(*token_ptr)->content;
			token_next = (t_token *)(*token_ptr)->next->content;
		}
	}
}
