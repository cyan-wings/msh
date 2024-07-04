/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:53:32 by myeow             #+#    #+#             */
/*   Updated: 2024/07/04 17:24:40 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * May want to add checks later on whether executable is of type WORD.
 */
static void	executable(t_token *token, t_ast **exec_node)
{
	char	*executable_name;

	executable_name = token->value;
	*exec_node = minishell_parse_astnew("executable", executable_name);
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
	minishell_tokenise_get_next_token(token_ptr);
	*args_node = minishell_parse_astnew("arguments", 0);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
		minishell_parse_cmd_arguments(token_ptr, args_node);
}

/*
 * Format of a simple command:
 * 		<redirections> <exec> <arguments> <redirections>
 *
 * 		redirections and arguments are optional.
 *
 * This function handles the format structure of the simple command.
 * The executable and arguments sandwiched between the optional redirections.
 */
static void	minishell_parse_cmd_helper(
		t_list **token_ptr,
		t_ast **redirs_node,
		t_ast **exec_node,
		t_ast **args_node
		)
{
	*redirs_node = minishell_parse_astnew("redirections", 0);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		minishell_parse_cmd_redirections(token_ptr, redirs_node);
	executable_arguments(token_ptr, exec_node, args_node);
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		minishell_parse_cmd_redirections(token_ptr, redirs_node);
}

/*
 * Initialisation of all the nodes (i.e., executable, arguments
 * 		and redirections)
 *
 * Only executable is mandatory, hence the if-guard.
 * Notes:
 * 		Adding a child node that is NULL will not mutate the parent.
 */
t_ast	*minishell_parse_cmd(t_list **token_ptr)
{
	t_ast	*redirs_node;
	t_ast	*exec_node;
	t_ast	*args_node;
	t_ast	*cmd_node;

	redirs_node = 0;
	exec_node = 0;
	args_node = 0;
	cmd_node = 0;
	cmd_node = minishell_parse_astnew("simple_command", 0);
	minishell_parse_cmd_helper(token_ptr, &redirs_node, &exec_node, &args_node);
	if (exec_node)
	{
		minishell_parse_astadd_child(cmd_node, exec_node);
		minishell_parse_astadd_child(cmd_node, args_node);
		minishell_parse_astadd_child(cmd_node, redirs_node);
		return (cmd_node);
	}
	return (0);
}
