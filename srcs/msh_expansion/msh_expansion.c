/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:02:10 by myeow             #+#    #+#             */
/*   Updated: 2024/07/11 19:43:25 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	msh_expansion_wildcards(char **strptr);

void	msh_expansion_quotes(char **strptr);

void	msh_expansion_dollar(char **strptr, t_list *env_list);

static void	msh_expansion_print_node(t_ast *node, t_list *env_list)
{
	int	j;

	ft_putstr_fd(node->type, 1);
	if (node->value)
	{
		//msh_expansion_dollar(&(node->value), env_list);
		//msh_expansion_quotes(&(node->value));
		msh_expansion_wildcards(&(node->value));
		ft_putstr_fd(": ", 1);
		ft_putchar_fd('[', 1);
		ft_putstr_fd(node->value, 1);
		ft_putchar_fd(']', 1);
	}
	ft_putstr_fd(" , ", 1);
	j = -1;
	while (++j < node->child_count)
		msh_expansion_print_node(node->children[j], env_list);
}

void	msh_expansion(t_ast *node, t_list *env_list)
{
	msh_expansion_print_node(node, env_list);
	return ;
}
