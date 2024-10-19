/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_init_get_argv_arr.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:23:18 by myeow             #+#    #+#             */
/*   Updated: 2024/10/19 15:30:06 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static int	check_null_param(t_ast *arguments_node, char ***argv_arr)
{
	if (!arguments_node)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init_get_argv_arr",
			"arguments_node is NULL.");
		return (0);
	}
	if (!argv_arr)
	{
		msh_perror("debug", "msh_execute_simple_cmd_init_get_argv_arr",
			"argv_arr is NULL.");
		return (0);
	}
	return (1);
}

static void	insert_args_to_argv_arr(t_ast *arguments_node, char ***argv_arr)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < arguments_node->child_count)
	{
		if (arguments_node->children[i]->value)
			(*argv_arr)[j++] = ft_strdup(arguments_node->children[i]->value);
		if ((*argv_arr)[j - 1] == NULL)
			return (msh_perror_exit("msh_execute_simple_cmd_init: get_argv_arr",
					"argv_arr[i]", "malloc fail.", EXIT_FAILURE));
	}
}

/*
 * Builds the argv for the execve function.
 * First element in the array must be the executable.
 * Note:
 * 		argv is always NULL terminated.
 * 		+ 2 due to the executable and the NULL terminator.
 * 		i is not incremented in the while loop becauase first index
 * 		of the arguments' child array is 0.
 */
void	msh_execute_simple_cmd_init_get_argv_arr(t_ast *arguments_node,
		char ***argv_arr)
{
	char	*executable_str;

	if (!check_null_param(arguments_node, argv_arr))
		return ;
	if (ft_strcmp(arguments_node->type, "arguments"))
		return (msh_perror_exit("debug",
				"msh_execute_simple_cmd_init: get_argv_arr",
				"Node is not arguments.", EXIT_FAILURE));
	executable_str = NULL;
	executable_str = arguments_node->children[0]->value;
	if (!executable_str || !*executable_str)
		return ;
	*argv_arr = (char **)ft_calloc(arguments_node->child_count + 1,
			sizeof(char *));
	if (!*argv_arr)
		return (msh_perror_exit("msh_execute_simple_cmd_init: get_argv_arr",
				"argv_arr", "malloc fail.", EXIT_FAILURE));
	insert_args_to_argv_arr(arguments_node, argv_arr);
}
