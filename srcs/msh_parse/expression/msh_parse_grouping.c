/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_grouping.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:12 by myeow             #+#    #+#             */
/*   Updated: 2024/09/05 20:20:27 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
 * 2 scenarios:
 *
 * 1st: list node is NULL means grammar is wrong.
 * 2nd: No closing bracket found. Hence, list_node has to be freed.
 */
t_ast	*msh_parse_grouping_error(t_ast **grouping_node,
		t_ast **list_node)
{
	msh_parse_astfree(grouping_node);
	msh_parse_astfree(list_node);
	return (0);
}

/*
 * A grouping is a list. However, an extra grouping node needs to be created
 * because subshells may be executed differently.
 */
t_ast	*msh_parse_grouping(t_list **token_ptr)
{
	t_ast	*grouping_node;
	t_ast	*list_node;

	if (ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
		return (0);
	msh_tokenise_get_next_token(token_ptr);
	grouping_node = 0;
	grouping_node = msh_parse_astnew("grouping", 0);
	list_node = 0;
	list_node = msh_parse_list(token_ptr);
	if (!list_node || !*token_ptr || \
			ft_strcmp(((t_token *)(*token_ptr)->content)->value, ")"))
		return (msh_parse_grouping_error(&grouping_node, &list_node));
	msh_tokenise_get_next_token(token_ptr);
	msh_parse_astadd_child(grouping_node, list_node);
	return (grouping_node);
}
