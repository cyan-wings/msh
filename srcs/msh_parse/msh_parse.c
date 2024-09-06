/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:46:15 by myeow             #+#    #+#             */
/*   Updated: 2024/09/06 18:36:08 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include "ft_print_utils.h"

int	msh_parse_token(t_list *token_list);

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
int	msh_parse(t_list *token_list, t_ast **root)
{
	t_ast	*expression_root_node;
	t_ast	*child_node;

	if (!msh_parse_token(token_list))
		return (0);
	else
		ft_putendl_fd("Parsing token success!", 1);
	child_node = msh_parse_list(&token_list);
	if (!child_node)
		return (0);
	expression_root_node = msh_parse_astnew("expression", 0);
	msh_parse_astadd_child(expression_root_node, child_node);
	*root = expression_root_node;
	ft_putendl_fd("Parsing successful, AST build complete", 1);
	return (1);
}
