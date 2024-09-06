/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:02:10 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 19:49:33 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_print_utils.h"
#include <unistd.h>

void	msh_expansion_wildcards_and_quotes(char **strptr);

void	msh_expansion_dollar(char **strptr, t_list *env_list);

static void	msh_expansion_aux(t_ast *node, t_list *env_list)
{
	int	j;

	if (node->value)
	{
		msh_expansion_dollar(&(node->value), env_list);
		msh_expansion_wildcards_and_quotes(&(node->value));
	}
	j = -1;
	while (++j < node->child_count)
		msh_expansion_aux(node->children[j], env_list);
}

void	msh_expansion(t_ast *node, t_list *env_list)
{
	msh_expansion_aux(node, env_list);
	return ;
}
