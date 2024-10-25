/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:46:15 by myeow             #+#    #+#             */
/*   Updated: 2024/10/21 20:07:38 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"
#include "ft_print_utils.h"

static int	check_null_param(t_list *token_list, t_ast **root)
{
	int	flag;

	flag = 1;
	if (!token_list)
	{
		msh_perror("debug", "msh_parse", "token_list is NULL.");
		flag = 0;
	}
	if (!root)
	{
		msh_perror("debug", "msh_parse", "root is NULL.");
		flag = 0;
	}
	return (flag);
}

int	msh_parse_token(t_list *token_list);

int	msh_parse_error(t_ast **child_node)
{
	msh_parse_astfree(child_node);
	return (ERROR);
}

/*
 * Description:
 * 		This is the parsing module. The main purpose of parsing is to ensure 
 * 		that the input grammar is valid. Each token is parsed first.
 * 		Then, an AST is build based on hierarchy of the input expression given.
 *
 * Return: 	0 if grammar parsing fails (i.e. child of root is NULL).
 * 			1 for parsing success.
 *
 * Subfolders:
 * 		expression	:Holds the parsing of list, pipeline, grouping and cmd.
 * 		ast			:Utilities for the ast(eg., create, insert node).
 * 		token		:Holds parsing and lexing of the tokens (word/operator).
 *
 * Notes:
 * 	(1)	When a new node fails to malloc in the heap,
 * 		msh process terminates.
 * 	(2)	Expression always begins with a list.
 * 	(3) Grouping is on par with a simple_cmd, hence grouping will be nested
 * 		in the list and pipeline.
 *
 */
int	msh_parse(t_list *token_list, t_ast **root, t_list *env_list)
{
	t_ast	*expression_root_node;
	t_ast	*child_node;
	int		status;

	if (!check_null_param(token_list, root))
		return (ERROR);
	if (!msh_parse_token(token_list))
		return (ERROR);
	child_node = NULL;
	status = 0;
	status = msh_parse_list(&token_list, &child_node, env_list);
	if (status)
		return (status);
	if (token_list)
		return (msh_parse_error(&child_node));
	expression_root_node = NULL;
	expression_root_node = msh_parse_astnew("expression", 0);
	msh_parse_astadd_child(expression_root_node, child_node);
	*root = expression_root_node;
	return (status);
}
