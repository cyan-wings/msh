/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_astnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:48 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:55:58 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

/*
 * Kill the whole msh processe if malloc error.
 */
t_ast	*msh_parse_astnew(char *type, char *value)
{
	t_ast	*node;

	node = (t_ast *) malloc(sizeof(t_ast));
	if (!node)
		msh_perror_exit("AST node malloc error.", 1);
	node->type = ft_strdup(type);
	node->value = NULL;
	if (value)
		node->value = ft_strdup(value);
	node->children = NULL;
	node->child_count = 0;
	return (node);
}
