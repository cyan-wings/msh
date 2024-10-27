/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_argument.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:43:54 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 17:51:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

static void	ast_add_argument_node(char *argument, t_ast **args_node)
{
	t_ast	*arg_child_node;

	arg_child_node = NULL;
	arg_child_node = msh_parse_astnew("argument", argument);
	msh_parse_astadd_child(*args_node, arg_child_node);
}

void	msh_parse_cmd_argument(t_list **token_ptr, t_ast **args_node)
{
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
	{
		ast_add_argument_node(((t_token *)(*token_ptr)->content)->value,
			args_node);
		msh_tokenise_get_next_token(token_ptr);
	}
}
