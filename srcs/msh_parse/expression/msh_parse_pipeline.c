/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:52 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 19:00:44 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_string_utils.h"

#define PIPE "|"
#define CMD 1
#define GROUP 2

static int	astadd_child_to_pipeline_node(t_list **token_ptr,
		t_ast **pipeline_node, int option)
{
	t_ast	*child;

	child = NULL;
	if (option == CMD)
		child = msh_parse_cmd(token_ptr);
	else if (option == GROUP)
		child = msh_parse_grouping(token_ptr);
	if (!child)
		return (0);
	msh_parse_astadd_child(*pipeline_node, child);
	return (1);
}

static int	msh_parse_pipeline_helper(t_list **token_ptr,
		t_ast **pipeline_node)
{
	int	status;

	status = 1;
	while (status && *token_ptr && \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, PIPE))
	{
		if (!((*token_ptr)->next))
			return (0);
		msh_tokenise_get_next_token(token_ptr);
		if (((t_token *)(*token_ptr)->content)->type == WORD ||
				((t_token *)(*token_ptr)->content)->type == REDIR_OP)
			status = astadd_child_to_pipeline_node(token_ptr, \
					pipeline_node, CMD);
		else if (!ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
			status = astadd_child_to_pipeline_node(token_ptr, \
					pipeline_node, GROUP);
		else
			status = 0;
	}
	return (status);
}

/*
 * A pipeline must consist at least 1 simple command.
 *
 * Notes:
 * 		A simple command can start with a WORD (which assumes the executable)
 * 		or a REDIR_OP (which assumes starts with redirection(s))
 */
t_ast	*msh_parse_pipeline(t_list **token_ptr)
{
	t_ast	*pipeline_node;
	int		status;

	if (!*token_ptr)
		return (NULL);
	pipeline_node = NULL;
	pipeline_node = msh_parse_astnew("pipeline", NULL);
	status = 1;
	if (!ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
		status = astadd_child_to_pipeline_node(token_ptr, \
				&pipeline_node, GROUP);
	else
		status = astadd_child_to_pipeline_node(token_ptr, \
				&pipeline_node, CMD);
	if (status && msh_parse_pipeline_helper(token_ptr, &pipeline_node))
		return (pipeline_node);
	msh_parse_astfree(&pipeline_node);
	return (NULL);
}
