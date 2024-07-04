/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_pipeline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:20:12 by myeow             #+#    #+#             */
/*   Updated: 2024/07/04 17:53:13 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PIPE "|"

/*
 * A pipeline must consist at least 1 simple command.
 *
 * Notes:
 * 		A simple command can start with a WORD (which assumes the executable)
 * 		or a REDIR_OP (which assumes starts with redirection(s))
 */
t_ast	*minishell_parse_pipeline(t_list **token_ptr)
{
	t_ast	*pipeline_node;
	t_ast	*cmd_node;

	pipeline_node = 0;
	pipeline_node = minishell_parse_astnew("pipeline", 0);
	cmd_node = 0;
	//No need for checks whether word or operator.
	cmd_node = minishell_parse_cmd(token_ptr);
	minishell_parse_astadd_child(pipeline_node, cmd_node);
	while (*token_ptr && \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, PIPE))
	{
		if (!((*token_ptr)->next))
			return (0);//return grammar error
		minishell_tokenise_get_next_token(token_ptr);
		if (((t_token *)(*token_ptr)->content)->type == WORD ||
				((t_token *)(*token_ptr)->content)->type == REDIR_OP)
		{
			cmd_node = minishell_parse_cmd(token_ptr);
			minishell_parse_astadd_child(pipeline_node, cmd_node);
		}
	}
	return (pipeline_node);
}
