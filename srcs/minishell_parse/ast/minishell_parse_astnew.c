/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_astnew.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:47:44 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 19:51:46 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*minishell_parse_astnew(char *type, char *value)
{
	t_ast	*node;

	node = (t_ast *) malloc(sizeof(t_ast));
	if (!node)
		minishell_perror_exit("AST node malloc error.", 1);
	node->type = ft_strdup(type);
	node->value = ft_strdup(value);
	node->children = NULL;
	node->child_count = 0;
	return (node);
}
