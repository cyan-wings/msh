/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:33:55 by myeow             #+#    #+#             */
/*   Updated: 2024/06/28 16:33:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Should put in STDERR?
 */
static void	minishell_parse_error(void)
{
	ft_putendl_fd("Parse Error", 1);
	return ;
}

static int	minishell_parse_token(t_list *token_list)
{
	t_token	*curr;

	while (token_list)
	{
		curr = (t_token *) token_list->content;
		if (!minishell_parse_word(curr) && \
				!minishell_parse_operator(curr, DEFAULT))
			return (0);
		token_list = token_list->next;
	}
	return (1);
}

void	minishell_parse(t_list *token_list)
{
	if (!minishell_parse_token(token_list))
		minishell_parse_error();
	return ;
}
