/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenise_free.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:50:06 by myeow             #+#    #+#             */
/*   Updated: 2024/06/28 17:50:08 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_t_token_clear(void *content)
{
	t_token	*token;
	char	*s;

	token = (t_token *) content;
	s = token->value;
	ft_memdel((void **) &s);
	free(content);
	return ;
}

void	minishell_tokenise_free(t_list **token_list)
{
	ft_lstclear(token_list, minishell_t_token_clear);
	return ;
}
