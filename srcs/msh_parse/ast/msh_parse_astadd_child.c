/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_astadd_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:04 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:43:37 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <stdlib.h>
#include "ft_mem_utils.h"

/*
 * Last space remain empty for the new child to be added.
 * Which is why child_count - 1.
 *
 * NICETOHAVE TODO: Find a more optimal solution to realloc number of nodes
 * (ex. geometric progression 1 2 4 8 16...)
 */
static t_ast	**children_realloc(t_ast ***old_children_ptr,
		int child_count)
{
	t_ast	**new_children;
	int		i;

	new_children = (t_ast **)malloc(sizeof(t_ast *) * child_count);
	if (!new_children)
	{
		msh_perror_exit("New ast child malloc error.", EXIT_FAILURE);
		return (NULL);
	}
	i = -1;
	while (++i < child_count - 1)
		new_children[i] = (*old_children_ptr)[i];
	ft_memdel((void **)old_children_ptr);
	return (new_children);
}

void	msh_parse_astadd_child(t_ast *parent, t_ast *child)
{
	if (!child)
		return ;
	parent->child_count++;
	parent->children = children_realloc(&(parent->children), \
			parent->child_count);
	parent->children[parent->child_count - 1] = child;
}
