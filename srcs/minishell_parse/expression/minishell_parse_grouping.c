/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_grouping.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 16:24:58 by myeow             #+#    #+#             */
/*   Updated: 2024/07/05 17:02:37 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	minishell_parse_astadd_child(grouping_node, list_node);
	if (ft_strcmp(((t_token *)(*token_ptr)->content)->value, ")"))
		return (0);//return grammar error, no close bracket
	return (grouping_node);
}
