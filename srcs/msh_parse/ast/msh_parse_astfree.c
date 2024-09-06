/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_astfree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:55:26 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:40:02 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_mem_utils.h"

void	msh_parse_astfree(t_ast **root_node)
{
	t_ast	*node;
	int		i;

	if (!root_node || !*root_node)
		return ;
	node = *root_node;
	i = -1;
	while (++i < node->child_count)
		msh_parse_astfree(&node->children[i]);
	ft_memdel((void **) &(node->type));
	if (node->value)
		ft_memdel((void **) &(node->value));
	ft_memdel((void **) &(node->children));
	ft_memdel((void **) &node);
}
