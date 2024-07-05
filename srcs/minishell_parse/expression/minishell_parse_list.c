/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:18 by myeow             #+#    #+#             */
/*   Updated: 2024/07/05 17:26:20 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define AND "&&"
#define OR "||"

/*
 * There are only 2 list operations: && and ||.
 */
static void	astadd_list_op_node(t_list **token_ptr, t_ast **list_root_node)
{
	char	*list_op;
	t_ast	*list_op_node;

	list_op = ((t_token *)(*token_ptr)->content)->value;
	list_op_node = 0;
	list_op_node = minishell_parse_astnew("list_op", list_op);
	minishell_parse_astadd_child(*list_root_node, list_op_node);
}

t_ast	*minishell_parse_list(t_list **token_ptr)
{
	t_ast	*list_root_node;
	t_ast	*pipeline_node;

	list_root_node = 0;
	list_root_node = minishell_parse_astnew("list", 0);
	pipeline_node = 0;
	pipeline_node = minishell_parse_pipeline(token_ptr);
	minishell_parse_astadd_child(list_root_node, pipeline_node);
	while (*token_ptr && \
			(!ft_strcmp(((t_token *)(*token_ptr)->content)->value, AND) || \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, OR)))
	{
		if (!((*token_ptr)->next))
			return (0);//return grammar error
		astadd_list_op_node(token_ptr, &list_root_node);
		minishell_tokenise_get_next_token(token_ptr);
		pipeline_node = minishell_parse_pipeline(token_ptr);
		minishell_parse_astadd_child(list_root_node, pipeline_node);
	}
	return (list_root_node);
}
