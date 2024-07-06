/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_grouping.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:24:58 by myeow             #+#    #+#             */
/*   Updated: 2024/07/06 22:04:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * 2 scenarios:
 *
 * 1st: list node is NULL means grammar is wrong.
 * 2nd: No closing bracket found. Hence, list_node has to be freed.
 */
t_ast	*minishell_parse_grouping_error(t_ast **grouping_node,
		t_ast **list_node)
{
	minishell_parse_astfree(grouping_node);
	minishell_parse_astfree(list_node);
	return (0);
}

/*
 * A grouping is a list. However, an extra grouping node needs to be created
 * because subshells may be executed differently.
 */
t_ast	*minishell_parse_grouping(t_list **token_ptr)
{
	t_ast	*grouping_node;
	t_ast	*list_node;

	if (ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
		return (0);
	minishell_tokenise_get_next_token(token_ptr);
	grouping_node = 0;
	grouping_node = minishell_parse_astnew("grouping", 0);
	list_node = 0;
	list_node = minishell_parse_list(token_ptr);
	if (!list_node || \
			ft_strcmp(((t_token *)(*token_ptr)->content)->value, ")"))
		return (minishell_parse_grouping_error(&grouping_node, &list_node));
	minishell_parse_astadd_child(grouping_node, list_node);
	return (grouping_node);
}
