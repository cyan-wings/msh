/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:10 by myeow             #+#    #+#             */
/*   Updated: 2024/10/24 20:51:55 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

int		msh_parse_cmd_redirection(t_list **token_ptr,
			t_ast **redirs_root_node, t_list *env_list);

void	msh_parse_cmd_argument(t_list **token_ptr, t_ast **args_node);

/*
 * Format of a simple command:
 * 		<redirections> <arguments> <redirections> <arguments> ...
 * 		<arguments> <redirections> <arguments> <redirections> ...
 * 
 * This function handles the format structure of the simple command.
 * Redirections and arguments can intertwine.
 * Each instance we encounter a redirection or an argument, it will
 * be processed and added to the parent redirections node or the 
 * parent arguments node.
 *
 * Notes: 	
 *
 * 	(1)	A valid redirection or an argument is mandatory and required.
 * 	(2) Following redirections or arguments are optional.
 *  (3) The 3rd if-statement is to check if there is a second set of
 *  	redirections.
 */
static int	msh_parse_cmd_helper(
		t_list **token_ptr,
		t_ast **redirs_node,
		t_ast **args_node,
		t_list *env_list
		)
{
	int		status;

	status = 0;
	if (*token_ptr)
	{
		if (((t_token *)(*token_ptr)->content)->type == REDIR_OP)
			status = msh_parse_cmd_redirection(token_ptr, redirs_node,
					env_list);
		else if (((t_token *)(*token_ptr)->content)->type == WORD)
			msh_parse_cmd_argument(token_ptr, args_node);
		else
			return (ERROR);
	}
	while (!status && *token_ptr && \
			(((t_token *)(*token_ptr)->content)->type == REDIR_OP || \
			((t_token *)(*token_ptr)->content)->type == WORD))
	{
		if (((t_token *)(*token_ptr)->content)->type == REDIR_OP)
			status = msh_parse_cmd_redirection(token_ptr, redirs_node,
					env_list);
		else if (((t_token *)(*token_ptr)->content)->type == WORD)
			msh_parse_cmd_argument(token_ptr, args_node);
	}
	return (status);
}

static int	msh_parse_cmd_error(
		t_ast **redirs_node,
		t_ast **args_node,
		t_ast **cmd_node,
		int status)
{
	msh_parse_astfree(redirs_node);
	msh_parse_astfree(args_node);
	msh_parse_astfree(cmd_node);
	return (status);
}

/*
 * Initialisation of all the nodes (i.e., executable, arguments
 * 		and redirections)
 *
 * Notes:
 * 		Adding a child node that is NULL will not mutate the parent.
 */
int	msh_parse_cmd(t_list **token_ptr, t_ast **cmd_node, t_list *env_list)
{
	t_ast	*redirs_node;
	t_ast	*args_node;
	int		status;

	if (!token_ptr)
		msh_perror("debug", "msh_parse_cmd", "token_ptr is NULL.");
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type != REDIR_OP
			&& ((t_token *)(*token_ptr)->content)->type != WORD)
		return (ERROR);
	redirs_node = NULL;
	args_node = NULL;
	redirs_node = msh_parse_astnew("redirections", NULL);
	args_node = msh_parse_astnew("arguments", NULL);
	*cmd_node = msh_parse_astnew("simple_command", NULL);
	status = 0;
	status = msh_parse_cmd_helper(token_ptr, &redirs_node, &args_node,
			env_list);
	if (!status && (args_node->child_count || redirs_node->child_count))
	{
		msh_parse_astadd_child(*cmd_node, args_node);
		msh_parse_astadd_child(*cmd_node, redirs_node);
		return (0);
	}
	return (msh_parse_cmd_error(&args_node, &redirs_node, cmd_node, status));
}
