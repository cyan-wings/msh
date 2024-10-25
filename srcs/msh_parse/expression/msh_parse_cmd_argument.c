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

char	*msh_parse_cmd_expand_word(char *word, t_list *env_list);

static void	ast_add_argument_node(char *argument, t_ast **args_node)
{
	t_ast	*arg_child_node;

	arg_child_node = NULL;
	arg_child_node = msh_parse_astnew("argument", argument);
	msh_parse_astadd_child(*args_node, arg_child_node);
}

static void	parse_globbing_argument(char *str, t_ast **args_node)
{
	char	**array;
	int		n;

	array = NULL;
	array = msh_utils_split(str, DELIM_R, "msh_parse_cmd_arguments",
			"parse_globbing_argument");
	n = -1;
	while (array[++n])
	{
		msh_utils_strrpad(&(array[n]), PAD_R);
		ast_add_argument_node(array[n], args_node);
	}
	ft_free_ft_split(array);
	ft_memdel((void **)&str);
}

static void	parse_multiple_argument(char *str, t_ast **args_node)
{
	char	**array;
	int		n;

	array = NULL;
	array = msh_utils_split(str, ' ', "msh_parse_cmd_arguments",
			"parse_multiple_argument");
	n = -1;
	while (array[++n])
		ast_add_argument_node(array[n], args_node);
	ft_free_ft_split(array);
	ft_memdel((void **)&str);
}

//It is valid for arg_str to be NULL.
//Example: $abc (which doesn't exist in env)
static void	parse_argument(char *arg_str, t_ast **args_node, t_list *env_list)
{
	char	*out;
	int		i;

	out = NULL;
	out = msh_parse_cmd_expand_word(arg_str, env_list);
	if (!out)
		return (ast_add_argument_node(NULL, args_node));
	if (ft_strchr(out, PAD_R))
		return (parse_globbing_argument(out, args_node));
	if (!ft_strchr(out, SPACE_R))
		return (parse_multiple_argument(out, args_node));
	i = -1;
	while (out[++i])
		if (out[i] == SPACE_R)
			out[i] = ' ';
	ast_add_argument_node(out, args_node);
	ft_memdel((void **)&out);
}

void	msh_parse_cmd_argument(		
		t_list **token_ptr,
		t_ast **args_node,
		t_list *env_list
		)
{
	if (*token_ptr && ((t_token *)(*token_ptr)->content)->type == WORD)
	{
		parse_argument(((t_token *)(*token_ptr)->content)->value,
			args_node, env_list);
		msh_tokenise_get_next_token(token_ptr);
	}
}
