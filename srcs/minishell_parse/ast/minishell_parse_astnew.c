/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_astnew.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:47:44 by myeow             #+#    #+#             */
/*   Updated: 2024/07/06 15:08:49 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Kill the whole minishell processe if malloc error.
 */
t_ast	*minishell_parse_astnew(char *type, char *value)
{
	t_ast	*node;

	node = (t_ast *) malloc(sizeof(t_ast));
	if (!node)
		minishell_perror_exit("AST node malloc error.", 1);
	node->type = ft_strdup(type);
	node->value = NULL;
	if (value)
		node->value = ft_strdup(value);
	node->children = NULL;
	node->child_count = 0;
	return (node);
}
