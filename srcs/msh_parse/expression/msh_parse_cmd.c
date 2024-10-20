/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:10 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 20:15:24 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

int		msh_parse_cmd_redirections(t_list **token_ptr,
			t_ast **redirs_root_node);

static t_ast	*argument(t_token *token)
{
	char	*argument_string;

	if (token->type != WORD)
		return (NULL);
	argument_string = token->value;
	return (msh_parse_astnew("argument", argument_string));
}

static void	parse_arguments(		
		t_list **token_ptr,
		t_ast **args_node
		)
{
	t_ast	*arg_child_node;

	while (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
	{
		arg_child_node = argument((t_token *)(*token_ptr)->content);
		msh_parse_astadd_child(*args_node, arg_child_node);
		msh_tokenise_get_next_token(token_ptr);
	}
}

/*
 * Format of a simple command:
 * 		<redirections> <arguments> <redirections>
 * 
 * Either are optional. But flag error if there is nothing.
 * This function handles the format structure of the simple command.
 * The executable and arguments sandwiched between the optional redirections.
 *
 * Notes: 	
 *
 * 	(1)	After the first set of redirections, if a WORD is present
 * 		it would be the executable.
 * 	(2) Following WORDs right after executable will be the arguments.
 * 		Refer to msh_parse_cmd_arguments.c
 *  (3) The 3rd if-statement is to check if there is a second set of
 *  	redirections.
 *  (4) After this, NO WORDS nor '(' or ')' should exist as it is the 
 *  	end of a simple command. That means we must follow it only by
 *  	PIPE or LIST_OPs.
 * 	(5) When parse error, function returns 0 and all freeing is done in
 * 		the outer function (i.e., msh_parse_cmd).
 *
 * MISC:	The redirections ast node is initialised here due to the fact
 * 			that redirections can occur from the front and back of the 
 * 			arguments.
 *
 * 			Arguments node will be added regardless 
 * 			whether there are available or not in the simple command.
 */
static int	msh_parse_cmd_helper(
		t_list **token_ptr,
		t_ast **redirs_node,
		t_ast **args_node
		)
{
	int		status;

	status = 0;
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		status = msh_parse_cmd_redirections(token_ptr, redirs_node);
	if (status)
		return (status);
	parse_arguments(token_ptr, args_node);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		status = msh_parse_cmd_redirections(token_ptr, redirs_node);
	if (status)
		return (status);
	return (0);
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
 * Only executable is mandatory, hence the if-guard.
 * Notes:
 * 		Adding a child node that is NULL will not mutate the parent.
 */
int	msh_parse_cmd(t_list **token_ptr, t_ast **cmd_node)
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
	status = msh_parse_cmd_helper(token_ptr, &redirs_node, &args_node);
	if (!status && (args_node->child_count || redirs_node->child_count))
	{
		msh_parse_astadd_child(*cmd_node, args_node);
		msh_parse_astadd_child(*cmd_node, redirs_node);
		return (0);
	}
	return (msh_parse_cmd_error(&args_node, &redirs_node, cmd_node, status));
}
