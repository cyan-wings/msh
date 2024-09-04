/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:10 by myeow             #+#    #+#             */
/*   Updated: 2024/09/04 20:29:19 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		msh_parse_cmd_redirections(t_list **token_ptr,
			t_ast **redirs_root_node);
void	msh_parse_cmd_arguments(t_list **token_ptr,
			t_ast **args_root_node);

/*
 * May want to add checks later on whether executable is of type WORD.
 */
static void	executable(t_token *token, t_ast **exec_node)
{
	char	*executable_name;

	executable_name = token->value;
	*exec_node = msh_parse_astnew("executable", executable_name);
}

/*
 * Parsing of the executable and arguments.
 */
static void	executable_arguments(		
		t_list **token_ptr,
		t_ast **exec_node,
		t_ast **args_node
		)
{
	executable((t_token *)(*token_ptr)->content, exec_node);
	msh_tokenise_get_next_token(token_ptr);
	*args_node = msh_parse_astnew("arguments", 0);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
		msh_parse_cmd_arguments(token_ptr, args_node);
}

static t_ast	*msh_parse_cmd_error(
		t_ast **redirs_node,
		t_ast **exec_node,
		t_ast **args_node,
		t_ast **cmd_node)
{
	msh_parse_astfree(exec_node);
	msh_parse_astfree(args_node);
	msh_parse_astfree(redirs_node);
	msh_parse_astfree(cmd_node);
	return (0);
}

/*
 * Format of a simple command:
 * 		<redirections> <exec> <arguments> <redirections>
 *
 * 		redirections and arguments are optional.
 *
 * This function handles the format structure of the simple command.
 * The executable and arguments sandwiched between the optional redirections.
 *
 * Notes: 	
 *
 * 	(1)	After the first set of redirections, a WORD must be present as
 * 		it would be the executable. Otherwise, return will cause
 * 		exec_node to remain null thus catching the grammar error.
 * 	(2)	2nd if-else block guarantees that executable must be of WORD type.
 * 	(3) When parse error, function returns 0 and all freeing is done in
 * 		the outer function (i.e., msh_parse_cmd).
 *
 * MISC:	The redirections ast node is initialised here due to the fact
 * 			that redirections can occur from the front and back of the 
 * 			executable and arguments.
 */
static int	msh_parse_cmd_helper(
		t_list **token_ptr,
		t_ast **redirs_node,
		t_ast **exec_node,
		t_ast **args_node
		)
{
	int		status;

	status = 1;
	*redirs_node = msh_parse_astnew("redirections", 0);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		status = msh_parse_cmd_redirections(token_ptr, redirs_node);
	if (!status || !*token_ptr || \
			(*token_ptr && ((t_token *)(*token_ptr)->content)->type != WORD))
		return (0);
	else
		executable_arguments(token_ptr, exec_node, args_node);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		status = msh_parse_cmd_redirections(token_ptr, redirs_node);
	if (!status)
		return (0);
	return (1);
}

/*
 * Initialisation of all the nodes (i.e., executable, arguments
 * 		and redirections)
 *
 * Only executable is mandatory, hence the if-guard.
 * Notes:
 * 		Adding a child node that is NULL will not mutate the parent.
 */
t_ast	*msh_parse_cmd(t_list **token_ptr)
{
	t_ast	*redirs_node;
	t_ast	*exec_node;
	t_ast	*args_node;
	t_ast	*cmd_node;
	int		status;

	redirs_node = 0;
	exec_node = 0;
	args_node = 0;
	cmd_node = 0;
	status = 1;
	cmd_node = msh_parse_astnew("simple_command", 0);
	status = msh_parse_cmd_helper(token_ptr, \
			&redirs_node, &exec_node, &args_node);
	if (exec_node && status)
	{
		msh_parse_astadd_child(cmd_node, exec_node);
		msh_parse_astadd_child(cmd_node, args_node);
		msh_parse_astadd_child(cmd_node, redirs_node);
		return (cmd_node);
	}
	return (msh_parse_cmd_error(&exec_node, \
				&args_node, &redirs_node, &cmd_node));
}
