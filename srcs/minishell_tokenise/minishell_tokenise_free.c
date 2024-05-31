/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenise_free.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:09:47 by myeow             #+#    #+#             */
/*   Updated: 2024/05/31 13:21:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_t_token_clear(void *content)
{
	t_token	*token;
	char	*s;

	token = (t_token *) content;
	s = token->string;
	ft_memdel((void **) &s);
	free(content);
	return ;
}

void	minishell_tokenise_free(t_list **token_list)
{
	ft_lstclear(token_list, minishell_t_token_clear);
	return;
}
