/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:33:55 by myeow             #+#    #+#             */
/*   Updated: 2024/07/05 17:58:25 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_parse(t_list *token_list, t_ast **root)
{
	t_ast	*expression_root_node;
	t_ast	*child_node;

	expression_root_node = minishell_parse_astnew("expression", 0);
	if (!minishell_parse_token(token_list))
		return (0);
	else
		ft_putendl_fd("Parsing token success!", 1);
	child_node = minishell_parse_list(&token_list);
	if (!child_node)
		return (0);//grammar error
	minishell_parse_astadd_child(expression_root_node, child_node);
	*root = expression_root_node;
	return (1);
}
