/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:30 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:58:55 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

#define AND "&&"
#define OR "||"

/*
 * 2 scenarios:
 * 	(1)	when pipeline_node is NULL which means there is parsing error.
 *	(2)	when current is AND or OR token but no token following it.
 *	
 *	Only free the list node as all pipeline_nodes and list_op_nodes are
 *	attached to the list_root_node.
 */
static t_ast	*msh_parse_list_error(t_ast **list_root_node)
{
	msh_parse_astfree(list_root_node);
	return (NULL);
}

/*
 * There are only 2 list operations: && and ||.
 */
static void	astadd_list_op_node(t_list **token_ptr, t_ast **list_root_node)
{
	char	*list_op;
	t_ast	*list_op_node;

	list_op = NULL;
	list_op = ((t_token *)(*token_ptr)->content)->value;
	list_op_node = NULL;
	list_op_node = msh_parse_astnew("list_op", list_op);
	msh_parse_astadd_child(*list_root_node, list_op_node);
}

static int	astadd_pipeline_node(t_list **token_ptr, t_ast **list_root_node)
{
	t_ast	*pipeline_node;

	pipeline_node = NULL;
	pipeline_node = msh_parse_pipeline(token_ptr);
	if (!pipeline_node)
		return (0);
	msh_parse_astadd_child(*list_root_node, pipeline_node);
	return (1);
}

t_ast	*msh_parse_list(t_list **token_ptr)
{
	t_ast	*list_root_node;

	if (!token_ptr)
		msh_perror("debug", "msh_parse_list", "token_ptr is NULL.");
	list_root_node = NULL;
	list_root_node = msh_parse_astnew("list", NULL);
	if (!astadd_pipeline_node(token_ptr, &list_root_node))
		return (msh_parse_list_error(&list_root_node));
	while (*token_ptr && \
			(!ft_strcmp(((t_token *)(*token_ptr)->content)->value, AND) || \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, OR)))
	{
		if (!((*token_ptr)->next))
			return (msh_parse_list_error(&list_root_node));
		astadd_list_op_node(token_ptr, &list_root_node);
		msh_tokenise_get_next_token(token_ptr);
		if (!astadd_pipeline_node(token_ptr, &list_root_node))
			return (msh_parse_list_error(&list_root_node));
	}
	return (list_root_node);
}
