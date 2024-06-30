/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:52:11 by myeow             #+#    #+#             */
/*   Updated: 2024/06/30 22:55:48 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_parse_word_string(char *str, int *idx);

int	minishell_parse_word(t_token *token)
{
	char	*str;
	int		idx;

	str = token->value;
	idx = 0;
	if (!str)
		return (0);
	token->type = WORD;
	return (minishell_parse_word_string(str, &idx));
}
