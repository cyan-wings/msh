/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_parse_cmd_argument.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:43:54 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 17:51:05 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_parse.h"

static void	ast_add_argument_node(char *argument, t_ast **args_node)
{
	t_ast	*arg_child_node;

	arg_child_node = NULL;
	arg_child_node = msh_parse_astnew("argument", argument);
	msh_parse_astadd_child(*args_node, arg_child_node);
}

static void	parse_multiple(char *str, t_ast **args_node)
{
	char	**array;
	int		n;

	array = NULL;
	array = msh_utils_split(str, DELIM_R, "msh_parse_cmd_arguments",
			"parse_globbing");
	n = -1;
	while (array[++n])
	{
		msh_utils_strrpad(&(array[n]), PAD_R);
		ast_add_argument_node(array[n], args_node);
	}
	ft_free_ft_split(array);
}

//It is valid for arg_str to be NULL.
//Example: $abc (which doesn't exist in env)
static void	parse_argument(char *arg_str, t_ast **args_node)
{
	int	i;

	if (!arg_str)
		return (ast_add_argument_node(NULL, args_node));
	i = -1;
	while (arg_str[++i])
	{
		if (arg_str[i] == '\"')
			while (arg_str[++i] != '\"')
				;
		if (arg_str[i] == '\'')
			while (arg_str[++i] != '\'')
				;
		if (arg_str[i] == ' ')
			arg_str[i] = DELIM_R;
	}
	if (ft_strchr(arg_str, DELIM_R) || ft_strchr (arg_str, PAD_R))
		return (parse_multiple(arg_str, args_node));
	msh_parse_expansion_quotes(&arg_str);
	ast_add_argument_node(arg_str, args_node);
}

void	msh_parse_cmd_argument(		
		t_list **token_ptr,
		t_ast **args_node,
		t_list *env_list
		)
{
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
	{
		msh_parse_expansion_dollar(
			&(((t_token *)(*token_ptr)->content)->value), env_list, 1);
		msh_parse_expansion_wildcards(
			&(((t_token *)(*token_ptr)->content)->value));
		parse_argument(((t_token *)(*token_ptr)->content)->value,
			args_node);
		msh_tokenise_get_next_token(token_ptr);
	}
}
