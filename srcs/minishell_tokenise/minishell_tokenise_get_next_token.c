/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenise_get_next_token.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:00:19 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 19:31:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * This is the consume function to iterate through the token_list.
 * There are no null guards/checks because we want to segfault on purpose
 * in case the token is null which is not supposed to happen.
 */
void	minishell_tokenise_get_next_token(t_list **token_ptr)
{
	*token_ptr = (*token_ptr)->next;
}
