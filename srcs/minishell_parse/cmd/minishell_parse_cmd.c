/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:53:32 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 19:55:58 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * May want to add checks later on whether executable is of type WORD.
 */
static t_ast	*executable(t_token *token)
{
	char	*executable_name;

	executable_name = token->value;
	return (minishell_parse_astnew("executable", executable_name));
}

t_ast	*minishell_parse_cmd(t_list **token_ptr)
{
	t_ast	*exec_node;
	t_ast	*args_node;
	//t_ast	*redirs_node;
	t_ast	*cmd_node;

	exec_node = executable((t_token *)(*token_ptr)->content);
	minishell_tokenise_get_next_token(token_ptr);
	if (*token_ptr)
	{
		if (((t_token *)(*token_ptr)->content)->type == WORD)
			args_node = minishell_parse_cmd_arguments(token_ptr);
		//parse redirs
	}
	cmd_node = minishell_parse_astnew("simple_command", 0);
	if (exec_node && args_node)
	{
		minishell_parse_astadd_child(cmd_node, exec_node);
		minishell_parse_astadd_child(cmd_node, args_node);
		return (cmd_node);
	}
	return (0);
}