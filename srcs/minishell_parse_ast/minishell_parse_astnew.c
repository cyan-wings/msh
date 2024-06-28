/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_astnew.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:47:44 by myeow             #+#    #+#             */
/*   Updated: 2024/06/28 17:44:41 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*minishell_parse_astnew(char *type, char *value)
{
	t_ast_node	*node = (t_ast_node *) malloc(sizeof(t_ast_node));
	node->type = ft_strdup(type);
	node->value = ft_strdup(value);
	node->children = NULL;
	node->child_count = 0;
	return (node);
}
