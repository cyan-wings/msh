/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:36:19 by myeow             #+#    #+#             */
/*   Updated: 2024/07/04 17:52:03 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contains(t_token *token, const char **ops, t_token_type token_type)
{
	while (*ops)
	{
		if (!ft_strcmp(token->value, *ops))
		{
			token->type = token_type;
			return (1);
		}
		++ops;
	}
	return (0);
}

int	minishell_parse_operator(t_token *token, t_operator_type type)
{
	static const char	*redir_ops[5] = {"<", ">", "<<", ">>", NULL};
	static const char	*ctrl_ops[6] = {"&&", "||", "|", "(", ")", NULL};

	if (type == DEFAULT)
		return (contains(token, redir_ops, REDIR_OP) + \
				contains(token, ctrl_ops, CTRL_OP));
	else if (type == REDIRECT)
		return (contains(token, redir_ops, REDIR_OP));
	else if (type == CONTROL)
		return (contains(token, ctrl_ops, CTRL_OP));
	return (0);
}
