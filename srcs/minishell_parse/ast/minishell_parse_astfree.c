/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_astfree.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:07:56 by myeow             #+#    #+#             */
/*   Updated: 2024/07/06 22:06:31 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_parse_astfree(t_ast **root_node)
{
	t_ast	*node;
	int		i;

	if (!root_node || !*root_node)
		return ;
	node = *root_node;
	i = -1;
	while (++i < node->child_count)
		minishell_parse_astfree(&node->children[i]);
	ft_memdel((void **) &(node->type));
	if (node->value)
		ft_memdel((void **) &(node->value));
	ft_memdel((void **) &(node->children));
	ft_memdel((void **) &node);
}
