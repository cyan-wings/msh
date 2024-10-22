/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_arguments.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:43:54 by myeow             #+#    #+#             */
/*   Updated: 2024/10/22 18:52:59 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

void	ft_strrpad(char **strptr, char padding);

static void	ast_add_argument_node(char *argument, t_ast **args_node)
{
	t_ast	*arg_child_node;

	arg_child_node = NULL;
	arg_child_node = msh_parse_astnew("argument", argument);
	msh_parse_astadd_child(*args_node, arg_child_node);
}

static void	parse_globbing(char *str, t_ast **args_node)
{
	char	**array;
	int		n;

	array = NULL;
	array = ft_split(str, DELIM_R);
	if (!array)
		return (msh_perror_exit("debug",
				"msh_parse_cmd_arguments: parse_globbing",
				"malloc fail.", EXIT_FAILURE));
	n = -1;
	while (array[++n])
	{
		ft_strrpad(&(array[n]), PAD_R);
		ast_add_argument_node(array[n], args_node);
	}
	ft_free_ft_split(array);
}

//It is valid for arg_str to be NULL.
//Example: $abc (which doesn't exist in env)
static void	parse_argument(char *arg_str, t_ast **args_node)
{
	if (!arg_str)
		return (ast_add_argument_node(NULL, args_node));
	if (ft_strchr(arg_str, PAD_R))
		return (parse_globbing(arg_str, args_node));
	ast_add_argument_node(arg_str, args_node);
}

void	msh_parse_cmd_arguments(		
		t_list **token_ptr,
		t_ast **args_node,
		t_list *env_list
		)
{
	while (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
	{
		msh_parse_expansion_dollar(
			&(((t_token *)(*token_ptr)->content)->value), env_list, 1);
		msh_parse_expansion_wildcards_and_quotes(
			&(((t_token *)(*token_ptr)->content)->value));
		parse_argument(((t_token *)(*token_ptr)->content)->value,
			args_node);
		msh_tokenise_get_next_token(token_ptr);
	}
}
