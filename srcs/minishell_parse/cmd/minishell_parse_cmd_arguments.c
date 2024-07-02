/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_cmd_arguments.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:14:50 by myeow             #+#    #+#             */
/*   Updated: 2024/07/02 21:05:15 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This may seem repeated code from executable. But having this function
 * separate is for extensibility and readability. New specific grammar
 * can be added for arguments, separate from executable.
 * For example: 
 * 		We may restrict arguments to always start with '-'. Split arguments
 * 		based on legit filenames and strings.
 */
static t_ast	*argument(t_token *token)
{
	char	*argument_string;

	if (token->type != WORD)
		return (0);
	argument_string = token->value;
	return (minishell_parse_astnew("argument", argument_string));
}

t_ast	*minishell_parse_cmd_arguments(t_list **token_ptr)
{
	t_ast	*args_root_node;
	t_token	*token;
	t_ast	*arg_child_node;

	args_root_node = minishell_parse_astnew("arguments", 0);
	token = (t_token *)(*token_ptr)->content;
	while (*token_ptr && token->type == WORD)
	{
		arg_child_node = argument(token);
		minishell_parse_astadd_child(args_root_node, arg_child_node);
		minishell_tokenise_get_next_token(token_ptr);
		if (*token_ptr)
			token = (t_token *)(*token_ptr)->content;
	}
	return (args_root_node);
}
