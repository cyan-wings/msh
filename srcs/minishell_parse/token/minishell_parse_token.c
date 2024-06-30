/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:44:54 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 19:55:01 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_parse_word(t_token *token);

int		minishell_parse_operator(t_token *token, t_operator_type type);

int	minishell_parse_token(t_list *token_list)
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
