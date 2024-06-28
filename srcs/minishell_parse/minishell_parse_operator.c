/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:36:19 by myeow             #+#    #+#             */
/*   Updated: 2024/06/27 18:23:23 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contains(t_token *token, const char **ops)
{
	while (*ops)
	{
		if (!ft_strcmp(token->value, *ops))
			return (1);
		++ops;
	}
	return (0);
}

int	minishell_parse_operator(t_token *token, t_operator_type type)
{
	static const char	*redir_ops[5] = {"<", ">", "<<", ">>", NULL};
	static const char	*ctrl_ops[6] = {"&&", "||", "|", "(", ")", NULL};

	if (type == DEFAULT)
		return (contains(token, redir_ops) + contains(token, ctrl_ops));
	else if (type == REDIRECT)
		return (contains(token, redir_ops));
	else if (type == CONTROL)
		return (contains(token, ctrl_ops));
	return (0);
}
