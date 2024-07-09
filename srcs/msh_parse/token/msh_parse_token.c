/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:47:42 by myeow             #+#    #+#             */
/*   Updated: 2024/07/09 13:47:51 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int		msh_parse_word(t_token *token);

int		msh_parse_operator(t_token *token, t_operator_type type);

int	msh_parse_token(t_list *token_list)
{
	t_token	*curr;
	int		word_flag;
	int		op_flag;

	word_flag = 0;
	op_flag = 0;
	while (token_list)
	{
		curr = (t_token *) token_list->content;
		word_flag = msh_parse_word(curr);
		op_flag = msh_parse_operator(curr, DEFAULT);
		if (word_flag + op_flag == 0)
			return (0);
		token_list = token_list->next;
	}
	return (1);
}