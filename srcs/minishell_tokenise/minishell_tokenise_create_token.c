/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tokenise_create_token.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:21:51 by myeow             #+#    #+#             */
/*   Updated: 2024/07/03 20:38:10 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*minishell_tokenise_create_token(char *str)
{
	t_token	*token;

	token = (t_token *) ft_memalloc(sizeof(t_token));
	if (!token)
		minishell_perror_exit("Token no mem", EXIT_FAILURE);
	token->value = str;
	return (token);
}
