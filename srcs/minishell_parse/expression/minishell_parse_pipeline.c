/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse_pipeline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:20:12 by myeow             #+#    #+#             */
/*   Updated: 2024/07/05 17:35:41 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PIPE "|"
#define CMD 1
#define GROUP 2

static void	astadd_child_to_pipeline_node(t_list **token_ptr,
		t_ast **pipeline_node, int option)
{
	t_ast	*child;

	child = 0;
	if (option == CMD)
		child = minishell_parse_cmd(token_ptr);
	else if (option == GROUP)
		child = minishell_parse_grouping(token_ptr);
	else
		return ;
	minishell_parse_astadd_child(*pipeline_node, child);
}

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

	pipeline_node = 0;
	pipeline_node = minishell_parse_astnew("pipeline", 0);
	if (!ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
		astadd_child_to_pipeline_node(token_ptr, &pipeline_node, GROUP);
	else
		astadd_child_to_pipeline_node(token_ptr, &pipeline_node, CMD);
	while (*token_ptr && \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, PIPE))
	{
		if (!((*token_ptr)->next))
			return (0);//return grammar error
		minishell_tokenise_get_next_token(token_ptr);
		if (((t_token *)(*token_ptr)->content)->type == WORD ||
				((t_token *)(*token_ptr)->content)->type == REDIR_OP)
			astadd_child_to_pipeline_node(token_ptr, &pipeline_node, CMD);
		else if (!ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
			astadd_child_to_pipeline_node(token_ptr, &pipeline_node, GROUP);
	}
	return (pipeline_node);
}
