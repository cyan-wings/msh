/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:02:10 by myeow             #+#    #+#             */
/*   Updated: 2024/10/19 22:50:07 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_expansion.h"

void	msh_expansion_wildcards_and_quotes(char **strptr);

void	msh_expansion_dollar(char **strptr, t_list *env_list, int quote);

static void	msh_expansion_aux(t_ast *node, t_list *env_list)
{
	int	j;

	if (!ft_strcmp(node->type, "heredoc") && node->value)
		msh_expansion_dollar(&(node->value), env_list, 0);
	else if (node->value)
	{
		msh_expansion_dollar(&(node->value), env_list, 1);
		msh_expansion_wildcards_and_quotes(&(node->value));
	}
	j = -1;
	while (++j < node->child_count)
		msh_expansion_aux(node->children[j], env_list);
}

void	msh_expansion(t_ast *node, t_list *env_list)
{
	if (!node)
		msh_perror("debug", "msh_expansion", "node is NULL.");
	if (!env_list)
		msh_perror("debug", "msh_expansion", "env_list is NULL.");
	msh_expansion_aux(node, env_list);
	return ;
}
