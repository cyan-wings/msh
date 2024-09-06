/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_token_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:48:03 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 19:08:17 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	msh_parse_token_word_string(char *str, int *idx);

int	msh_parse_token_word(t_token *token)
{
	char	*str;
	int		idx;

	str = token->value;
	idx = 0;
	if (!str)
		return (0);
	token->type = WORD;
	return (msh_parse_token_word_string(str, &idx));
}
