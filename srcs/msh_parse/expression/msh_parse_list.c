/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:30 by myeow             #+#    #+#             */
/*   Updated: 2024/10/21 20:36:18 by myeow            ###   ########.fr       */
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
 *	attached to the list_node.
 */
static int	msh_parse_list_error(t_ast **list_node, int status)
{
	msh_parse_astfree(list_node);
	return (status);
}

/*
 * There are only 2 list operations: && and ||.
 */
static void	astadd_list_op_node(t_list **token_ptr, t_ast **list_node)
{
	char	*list_op;
	t_ast	*list_op_node;

	list_op = NULL;
	list_op = ((t_token *)(*token_ptr)->content)->value;
	list_op_node = NULL;
	list_op_node = msh_parse_astnew("list_op", list_op);
	msh_parse_astadd_child(*list_node, list_op_node);
}

static int	astadd_pipeline_node(t_list **token_ptr, t_ast **list_node,
		t_list *env_list)
{
	t_ast	*pipeline_node;
	int		status;

	pipeline_node = NULL;
	status = 0;
	status = msh_parse_pipeline(token_ptr, &pipeline_node, env_list);
	if (status)
		return (status);
	msh_parse_astadd_child(*list_node, pipeline_node);
	return (0);
}

/*
 * A must consist of at least 1 pipeline node.
 *
 * Notes:
 * 		list operators are chained as nodes to the parent list node.
 */
int	msh_parse_list(t_list **token_ptr, t_ast **list_node, t_list *env_list)
{
	int	status;

	if (!token_ptr)
		msh_perror("debug", "msh_parse_list", "token_ptr is NULL.");
	if (!list_node)
		msh_perror("debug", "msh_parse_list", "list_node is NULL.");
	status = 0;
	*list_node = msh_parse_astnew("list", NULL);
	status = astadd_pipeline_node(token_ptr, list_node, env_list);
	if (status)
		return (msh_parse_list_error(list_node, status));
	while (*token_ptr && \
			(!ft_strcmp(((t_token *)(*token_ptr)->content)->value, AND) || \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, OR)))
	{
		if (!((*token_ptr)->next))
			return (msh_parse_list_error(list_node, ERROR));
		astadd_list_op_node(token_ptr, list_node);
		msh_tokenise_get_next_token(token_ptr);
		status = astadd_pipeline_node(token_ptr, list_node, env_list);
		if (status)
			return (msh_parse_list_error(list_node, status));
	}
	return (status);
}
