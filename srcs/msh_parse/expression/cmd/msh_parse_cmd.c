/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:10 by myeow             #+#    #+#             */
/*   Updated: 2024/09/05 22:54:21 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		msh_parse_cmd_redirections(t_list **token_ptr,
			t_ast **redirs_root_node);
void	msh_parse_cmd_arguments(t_list **token_ptr,
			t_ast **args_root_node);

/*
 * Parsing of the executable and arguments.
 * This function will run regardless whether there are executable
 * and arguments.
 * The first if-statement checks if a WORD is found right after redirections.
 * If there is, the WORD is treated as the executable.
 * Following WORDs will be treated as arguments.
 * "arguments" node value will always be NULL since each argument
 * of a simple command will be an individual "argument" node which will
 * be the child of the "arguments" node. Refer to msh_parse_cmd_arguments.c
 */
static void	executable_arguments(		
		t_list **token_ptr,
		t_ast **exec_node,
		t_ast **args_node
		)
{
	char	*executable_name;

	executable_name = NULL;
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
	{
		executable_name = ((t_token *)(*token_ptr)->content)->value;
		msh_tokenise_get_next_token(token_ptr);
	}
	*exec_node = msh_parse_astnew("executable", executable_name);
	*args_node = msh_parse_astnew("arguments", NULL);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
		msh_parse_cmd_arguments(token_ptr, args_node);
}

/*
 * Format of a simple command:
 * 		<redirections> <exec> <arguments> <redirections>
 * 		**redirections and arguments are optional in this case
 *
 * 							or
 *
 * 		<redirection> <redirections> <exec> <arguments> <redirections>
 * 		**redirections, exec and arguments are optional in this case
 *
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
 * 			executable and arguments.
 *
 * 			Executable and arguments node will be added regardless 
 * 			whether there are available or not in the simple command.
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
	*redirs_node = msh_parse_astnew("redirections", NULL);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		status = msh_parse_cmd_redirections(token_ptr, redirs_node);
	if (!status)
		return (0);
	executable_arguments(token_ptr, exec_node, args_node);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		status = msh_parse_cmd_redirections(token_ptr, redirs_node);
	if (!status)
		return (0);
	if (*token_ptr && (((t_token *)(*token_ptr)->content)->type == WORD
		|| !ft_strcmp(((t_token *)(*token_ptr)->content)->value, "(")
		|| !ft_strcmp(((t_token *)(*token_ptr)->content)->value, ")")))
		return (0);
	return (1);
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
	return (NULL);
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

	redirs_node = NULL;
	exec_node = NULL;
	args_node = NULL;
	cmd_node = NULL;
	status = 1;
	cmd_node = msh_parse_astnew("simple_command", NULL);
	status = msh_parse_cmd_helper(token_ptr, \
			&redirs_node, &exec_node, &args_node);
	if (status && (exec_node || redirs_node))
	{
		msh_parse_astadd_child(cmd_node, exec_node);
		msh_parse_astadd_child(cmd_node, args_node);
		msh_parse_astadd_child(cmd_node, redirs_node);
		return (cmd_node);
	}
	return (msh_parse_cmd_error(&exec_node, \
				&args_node, &redirs_node, &cmd_node));
}
