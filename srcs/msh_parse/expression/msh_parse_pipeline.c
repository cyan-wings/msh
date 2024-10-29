/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:51:52 by myeow             #+#    #+#             */
/*   Updated: 2024/10/21 20:36:34 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

#define PIPE "|"
#define CMD 1
#define GROUP 2

static int	astadd_child_to_pipeline_node(t_list **token_ptr,
		t_ast **pipeline_node, int option, t_list *env_list)
{
	t_ast	*child;
	int		status;

	child = NULL;
	status = 0;
	if (option == CMD)
		status = msh_parse_cmd(token_ptr, &child, env_list);
	else if (option == GROUP)
		status = msh_parse_grouping(token_ptr, &child, env_list);
	else
		msh_perror("debug",
			"msh_parse_pipeline: astadd_child_to_pipeline_node",
			"undefined option");
	if (status)
		return (status);
	msh_parse_astadd_child(*pipeline_node, child);
	return (0);
}

static int	msh_parse_pipeline_helper(t_list **token_ptr,
		t_ast **pipeline_node, t_list *env_list)
{
	int	status;

	status = 0;
	while (!status && *token_ptr && \
			!ft_strcmp(((t_token *)(*token_ptr)->content)->value, PIPE))
	{
		if (!((*token_ptr)->next))
			return (ERROR);
		msh_tokenise_get_next_token(token_ptr);
		if (((t_token *)(*token_ptr)->content)->type == WORD ||
				((t_token *)(*token_ptr)->content)->type == REDIR_OP)
			status = astadd_child_to_pipeline_node(token_ptr, \
					pipeline_node, CMD, env_list);
		else if (!ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
			status = astadd_child_to_pipeline_node(token_ptr, \
					pipeline_node, GROUP, env_list);
		else
			status = ERROR;
	}
	return (status);
}

/*
 * A pipeline must consist at least 1 simple command or a grouping.
 *
 * Notes:
 * 		A simple command can start with a WORD (which assumes the executable)
 * 		or a REDIR_OP (which assumes starts with redirection(s)).
 * 		A grouping must start with a '('.
 */
int	msh_parse_pipeline(t_list **token_ptr, t_ast **pipeline_node,
		t_list *env_list)
{
	int		status;

	if (!token_ptr)
		msh_perror("debug", "msh_parse_pipeline", "token_ptr is NULL.");
	if (!*token_ptr)
		return (ERROR);
	*pipeline_node = msh_parse_astnew("pipeline", NULL);
	status = 0;
	if (!ft_strcmp(((t_token *)(*token_ptr)->content)->value, "("))
		status = astadd_child_to_pipeline_node(token_ptr, \
				pipeline_node, GROUP, env_list);
	else
		status = astadd_child_to_pipeline_node(token_ptr, \
				pipeline_node, CMD, env_list);
	if (!status)
	{
		status = msh_parse_pipeline_helper(token_ptr, pipeline_node, env_list);
		if (!status)
			return (0);
	}
	msh_parse_astfree(pipeline_node);
	return (status);
}
