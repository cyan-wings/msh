/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_grouping.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:12 by myeow             #+#    #+#             */
/*   Updated: 2024/10/21 20:35:57 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

/*
 * 2 scenarios for error to occur:
 *
 * 1st: list node is NULL means parsing grammar is wrong.
 * 2nd: No closing bracket found. Hence, list_node has to be freed also.
 */
static int	msh_parse_grouping_error(t_ast **grouping_node,
		t_ast **list_node)
{
	if (grouping_node)
		msh_parse_astfree(grouping_node);
	if (list_node)
		msh_parse_astfree(list_node);
	return (ERROR);
}

/*
 * A grouping is a list. However, an extra grouping node needs to be created
 * because subshells may be executed differently.
 */
int	msh_parse_grouping(t_list **token_ptr, t_ast **grouping_node,
		t_list *env_list)
{
	t_ast	*list_node;
	int		status;

	if (!token_ptr)
		msh_perror("debug", "msh_parse_grouping", "token_ptr is NULL.");
	if (ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
		return (ERROR);
	msh_tokenise_get_next_token(token_ptr);
	*grouping_node = msh_parse_astnew("grouping", NULL);
	list_node = NULL;
	status = 0;
	status = msh_parse_list(token_ptr, &list_node, env_list);
	if (status)
		return (msh_parse_grouping_error(grouping_node, NULL));
	else if (!*token_ptr || \
			ft_strcmp(((t_token *)(*token_ptr)->content)->value, ")"))
		return (msh_parse_grouping_error(grouping_node, &list_node));
	msh_tokenise_get_next_token(token_ptr);
	msh_parse_astadd_child(*grouping_node, list_node);
	return (0);
}
