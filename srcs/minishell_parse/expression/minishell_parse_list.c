/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:38:18 by myeow             #+#    #+#             */
/*   Updated: 2024/07/06 22:00:42 by myeow            ###   ########.fr       */
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

/*
 * 2 scenarios:
 * 	(1)	when pipeline_node is NULL which means there is parsing error.
 *	(2)	when current is AND or OR token but no token following it.
 *		Requires freeing of both nodes for this scenario.
 */
t_ast	*minishell_parse_list_error(t_ast **list_root_node,
		t_ast **pipeline_node)
{
	minishell_parse_astfree(list_root_node);
	minishell_parse_astfree(pipeline_node);
	return (0);
}

t_ast	*minishell_parse_list(t_list **token_ptr)
{
	t_ast	*list_root_node;
	t_ast	*pipeline_node;

	list_root_node = 0;
	list_root_node = minishell_parse_astnew("list", 0);
	pipeline_node = 0;
	pipeline_node = minishell_parse_pipeline(token_ptr);
	if (!pipeline_node)
		return (minishell_parse_list_error(&list_root_node, &pipeline_node));
	minishell_parse_astadd_child(list_root_node, pipeline_node);
	while (*token_ptr && \
			(!ft_strcmp(((t_token *)(*token_ptr)->content)->value, AND) || \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, OR)))
	{
		if (!pipeline_node || !((*token_ptr)->next))
			return (minishell_parse_list_error(&list_root_node, \
						&pipeline_node));
		astadd_list_op_node(token_ptr, &list_root_node);
		minishell_tokenise_get_next_token(token_ptr);
		pipeline_node = minishell_parse_pipeline(token_ptr);
		minishell_parse_astadd_child(list_root_node, pipeline_node);
	}
	return (list_root_node);
}
