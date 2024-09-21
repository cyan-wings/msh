/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_astnew.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:48 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:45:26 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

static t_ast	*malloc_fail(char *name)
{
	msh_perror_exit("msh_parse_astnew", name, "malloc fail.", EXIT_FAILURE);
	return (NULL);
}

//value can be NULL
t_ast	*msh_parse_astnew(char *type, char *value)
{
	t_ast	*node;

	if (!type)
		msh_perror("debug", "msh_parse_astnew", "type is NULL");
	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (malloc_fail("node"));
	node->type = ft_strdup(type);
	if (!node->type)
		return (malloc_fail("node->type"));
	node->value = NULL;
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (malloc_fail("node->value"));
	}
	node->children = NULL;
	node->child_count = 0;
	return (node);
}
