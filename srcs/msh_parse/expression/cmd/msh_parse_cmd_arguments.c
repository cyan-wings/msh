/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:53:28 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:53:37 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

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
	return (msh_parse_astnew("argument", argument_string));
}

void	msh_parse_cmd_arguments(t_list **token_ptr,
		t_ast **args_root_node)
{
	t_token	*token;
	t_ast	*arg_child_node;

	token = (t_token *)(*token_ptr)->content;
	while (*token_ptr && token->type == WORD)
	{
		arg_child_node = argument(token);
		msh_parse_astadd_child(*args_root_node, arg_child_node);
		msh_tokenise_get_next_token(token_ptr);
		if (*token_ptr)
			token = (t_token *)(*token_ptr)->content;
	}
}
