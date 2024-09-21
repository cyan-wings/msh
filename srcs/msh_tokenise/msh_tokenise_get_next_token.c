/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tokenise_get_next_token.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:59:39 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:59:58 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_tokenise.h"

/*
 * This is the consume function to iterate through the token_list.
 * There are no null guards/checks because we want to segfault on purpose
 * in case the token is null which is not supposed to happen.
 */
void	msh_tokenise_get_next_token(t_list **token_ptr)
{
	*token_ptr = (*token_ptr)->next;
}
