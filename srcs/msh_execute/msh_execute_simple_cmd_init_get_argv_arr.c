/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_init_get_argv_arr.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:23:18 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:58:20 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"
#include "msh_expansion.h"

static int	get_args_count(char *expanded_word, char delim)
{
	char	**temp;
	int		ret;

	temp = NULL;
	temp = msh_utils_split(expanded_word, delim,
			"msh_execute_simple_cmd_init_get_argv_arr",
			"count_args_in_word");
	ret = 0;
	ret = msh_utils_arraylen(temp);
	ft_free_ft_split(temp);
	return (ret);
}

static int	count_args_in_word(char *expanded_word)
{
	if (!expanded_word)
		return (0);
	if (ft_strchr(expanded_word, PAD_R))
		return (get_args_count(expanded_word, DELIM_R));
	if (!ft_strchr(expanded_word, SPACE_R) && ft_strchr(expanded_word, ' '))
		return (get_args_count(expanded_word, ' '));
	return (1);
}

void	msh_execute_simple_cmd_init_get_argv_arr_helper(t_ast *arguments_node,
				char ***argv_arr, int argv_arr_len, char **temp_arr);

void	msh_execute_simple_cmd_init_get_argv_arr(t_ast *arguments_node,
		char ***argv_arr, t_list **env_list)
{
	int		argv_arr_len;
	char	**temp_arr;
	int		i;
	char	*expanded_word;

	argv_arr_len = 0;
	temp_arr = (char **)ft_calloc(arguments_node->child_count + 1,
			sizeof(char *));
	i = -1;
	while (++i < arguments_node->child_count)
	{
		expanded_word = NULL;
		expanded_word = msh_expansion_word(arguments_node->children[i]->value,
				*env_list);
		if (!i && !expanded_word)
		{
			ft_free_ft_split(temp_arr);
			return ;
		}
		temp_arr[i] = expanded_word;
		argv_arr_len += count_args_in_word(expanded_word);
	}
	return (msh_execute_simple_cmd_init_get_argv_arr_helper(arguments_node,
			argv_arr, argv_arr_len, temp_arr));
}
