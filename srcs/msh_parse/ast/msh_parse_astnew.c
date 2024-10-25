/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_astnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:48 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 16:08:42 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

//value can be NULL
t_ast	*msh_parse_astnew(char *type, char *value)
{
	t_ast	*node;

	if (!type)
		msh_perror("debug", "msh_parse_astnew", "type is NULL");
	node = NULL;
	node = (t_ast *)msh_utils_memalloc(sizeof(t_ast), "msh_parse_astnew",
			"node");
	node->type = NULL;
	node->type = msh_utils_strdup(type, "msh_parse_astnew", "node->type");
	node->value = NULL;
	if (value)
		node->value = msh_utils_strdup(value, "msh_parse_astnew",
				"node->value");
	node->children = NULL;
	node->child_count = 0;
	return (node);
}
