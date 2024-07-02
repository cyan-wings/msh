/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_astadd_child.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:44:08 by myeow             #+#    #+#             */
/*   Updated: 2024/07/01 19:25:48 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Last space remain empty for the new child to be added.
 * Which is why child_count - 1.
 */
static t_ast	**children_realloc(t_ast ***old_children_ptr,
		int child_count)
{
	t_ast	**new_children;
	int		i;

	new_children = (t_ast **) malloc(sizeof(t_ast *) * child_count);
	if (!new_children)
	{
		minishell_perror_exit("New ast child malloc error.", 1);
		return (0);
	}
	i = -1;
	while (++i < child_count - 1)
		new_children[i] = (*old_children_ptr)[i];
	free(*old_children_ptr);
	*old_children_ptr = 0;
	return (new_children);
}

void	minishell_parse_astadd_child(t_ast *parent, t_ast *child)
{
	if (!child)
		return ;
	parent->child_count++;
	parent->children = children_realloc(&(parent->children), \
			parent->child_count);
	parent->children[parent->child_count - 1] = child;
}
