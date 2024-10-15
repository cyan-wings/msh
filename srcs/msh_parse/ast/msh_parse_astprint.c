/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_astprint.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:56:09 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:39:36 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

void	msh_parse_astprint(t_ast *node, int indent, int null_flag)
{
	int	i;
	int	j;

	if (!node)
		msh_perror("debug", "msh_parse_astprint", "node is NULL");
	i = -1;
	while (++i < indent)
		ft_putstr_fd("\t", STDIN_FILENO);
	ft_putstr_fd(node->type, STDIN_FILENO);
	ft_putstr_fd(": ", STDIN_FILENO);
	if (node->value)
		ft_putendl_fd(node->value, STDIN_FILENO);
	else
	{
		if (null_flag)
			ft_putendl_fd("NULL", STDIN_FILENO);
	}
	j = -1;
	while (++j < node->child_count)
	{
		ft_putchar_fd('\n', STDIN_FILENO);
		msh_parse_astprint(node->children[j], indent + 1, null_flag);
	}
	ft_putchar_fd('\n', STDIN_FILENO);
}
