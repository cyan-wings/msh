/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:33:55 by myeow             #+#    #+#             */
/*   Updated: 2024/07/03 16:00:06 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Should put in STDERR?
 */
static void	minishell_parse_error(void)
{
	ft_putendl_fd("Parse Error!", 1);
	return ;
}

void	minishell_parse(t_list *token_list)
{
	t_ast	*root;

	if (!minishell_parse_token(token_list))
		minishell_parse_error();
	else
		ft_putendl_fd("Parsing success!", 1);
	return ;
	root = minishell_parse_cmd(&token_list);
	minishell_parse_astprint(root, 0);
	return ;
}
