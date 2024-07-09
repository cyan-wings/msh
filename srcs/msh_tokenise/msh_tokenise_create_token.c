/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_tokenise_create_token.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:59:03 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:59:11 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_token	*msh_tokenise_create_token(char *str)
{
	t_token	*token;

	token = (t_token *) ft_memalloc(sizeof(t_token));
	if (!token)
		msh_perror_exit("Token no mem", EXIT_FAILURE);
	token->value = str;
	return (token);
}
