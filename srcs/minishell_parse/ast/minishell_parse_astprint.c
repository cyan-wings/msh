/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_astprint.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:16:16 by myeow             #+#    #+#             */
/*   Updated: 2024/07/05 17:37:32 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_parse_astprint(t_ast *node, int indent)
{
	int	i;
	int	j;

	if (!node)
		return ;
	i = -1;
	while (++i < indent)
		ft_putstr_fd("\t", 1);
	ft_putstr_fd(node->type, 1);
	if (node->value)
	{
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(node->value, 1);
		ft_putchar_fd('\n', 1);
	}
	j = -1;
	while (++j < node->child_count)
	{
		ft_putchar_fd('\n', 1);
		minishell_parse_astprint(node->children[j], indent + 1);
	}
	ft_putchar_fd('\n', 1);
}
