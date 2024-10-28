/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute_simple_cmd_init_get_argv_arr_helper.c  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeow <myeow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 07:23:18 by myeow             #+#    #+#             */
/*   Updated: 2024/10/25 15:58:20 by myeow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_execute.h"

static void	insert_globbing_arg(char *expanded_word, char **argv_arr, int *j)
{
	char	**array;
	int		n;
	char	*temp;

	array = NULL;
	array = msh_utils_split(expanded_word, DELIM_R, "msh_parse_cmd_arguments",
			"parse_globbing_argument");
	n = -1;
	while (array[++n])
	{
		temp = NULL;
		temp = msh_utils_strdup(array[n],
				"msh_execute_simple_cmd_init_get_argv_arr_helper",
				"insert_globbing_arg");
		msh_utils_strrpad(&temp, PAD_R);
		argv_arr[(*j)++] = temp;
	}
	ft_free_ft_split(array);
}

static void	insert_multiple_arg(char *expanded_word, char **argv_arr, int *j)
{
	char	**array;
	int		n;
	char	*temp;
	int		i;

	array = NULL;
	array = msh_utils_split(expanded_word, ' ', "msh_parse_cmd_arguments",
			"parse_multiple_argument");
	n = -1;
	while (array[++n])
	{
		temp = NULL;
		temp = msh_utils_strdup(array[n],
				"msh_execute_simple_cmd_init_get_argv_arr_helper",
				"insert_globbing_arg");
		i = -1;
		while (temp[++i])
			if (temp[i] == SPACE_R)
				temp[i] = ' ';
		argv_arr[(*j)++] = temp;
	}
	ft_free_ft_split(array);
}

static void	insert_args_to_argv_arr(char *expanded_word, char **argv_arr,
		int *j)
{
	int	i;

	if (!expanded_word)
		return ;
	if (ft_strchr(expanded_word, PAD_R))
		return (insert_globbing_arg(expanded_word, argv_arr, j));
	if (!ft_strchr(expanded_word, SPACE_R) && ft_strchr(expanded_word, ' '))
		return (insert_multiple_arg(expanded_word, argv_arr, j));
	i = -1;
	while (expanded_word[++i])
		if (expanded_word[i] == SPACE_R)
			expanded_word[i] = ' ';
	argv_arr[(*j)++] = msh_utils_strdup(expanded_word,
			"msh_execute_simple_cmd_init_get_argv_arr_helper",
			"insert_args_to_argv_arr");
}

void	msh_execute_simple_cmd_init_get_argv_arr_helper(t_ast *arguments_node,
		char ***argv_arr, int argv_arr_len, char **temp_arr)
{
	int	i;
	int	j;

	*argv_arr = (char **)ft_calloc(argv_arr_len + 1,
			sizeof(char *));
	if (!*argv_arr)
		return (msh_perror_exit("msh_execute_simple_cmd_init_get_argv_arr",
				"argv_arr", "malloc fail.", EXIT_FAILURE));
	j = 0;
	i = -1;
	while (++i < arguments_node->child_count)
		insert_args_to_argv_arr(temp_arr[i], *argv_arr, &j);
	ft_free_ft_split(temp_arr);
}
